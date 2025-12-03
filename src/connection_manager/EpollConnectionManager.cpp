/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:25:34 by capapes           #+#    #+#             */
/*   Updated: 2025/12/01 18:53:13 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// c++ -Wall -Wextra -Werror -std=c++98 -MMD -g *.cpp ../URI_parsing/**/*.cpp -I../URI_parsing/ -I../URI_parsing/utils -I../http_request_parser

#include "EpollConnectionManager.hpp"
#include <stdlib.h>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include "Log.hpp"
#include "../http_request_parser/Schemas.hpp"
#include "colors.hpp"
#include "../http_request_parser/ReqScanner.hpp"

#include <sys/wait.h>



// =====================================================================
// 	        MESSAGES
// =====================================================================
void serverUpMessage(int port) {
    std::cout << COLOR_GREEN << "✔ Server up and running "
      << COLOR_CYAN   << "on port "
      << COLOR_YELLOW << port
      << COLOR_RESET  << std::endl;
}

// =====================================================================
//       UTILS
// =====================================================================
double getCurrentTimeMs() {
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (static_cast<double>(tv.tv_sec) * 1000.0) +
           (static_cast<double>(tv.tv_usec) / 1000.0);
}

void EpollConnectionManager::setInstance(int fd, uint32_t events, int op) {
    epoll_event ev;
    
    memset(&ev, 0, sizeof(ev));
    ev.events = events | EPOLLET;
    ev.data.fd = fd;
    
    if (epoll_ctl(epfd, op, fd, &ev) == -1)
        exitWithError("Failed to set epoll instance");
  
}

void EpollConnectionManager::exitWithError(const std::string& message) {
    std::cerr << COLOR_RED << "✘ " << message << COLOR_RESET << std::endl;
    exit(EXIT_FAILURE);
}

// =====================================================================
// 	CONNECTION MANAGER CONSTRUCTOR
// =====================================================================

EpollConnectionManager::EpollConnectionManager(std::map<int, Socket*> socks, ServerManager server) 
    : epfd(-1), listeningSockets(socks), serverManager(server)
{
    if (socks.empty())
        return;
    epfd = epoll_create1(0);
    if (epfd == -1)
        exitWithError("Failed to create epoll file descriptor");
    for (std::map<int, Socket*>::iterator it = listeningSockets.begin(); it != listeningSockets.end(); ++it)
    {
        setInstance(it->first, EPOLLIN, EPOLL_CTL_ADD);
        serverUpMessage(it->second->getPort());
        EventLog::log(EPOLL_ADD_SOCKET, it->first);
    }
    run();
}

void EpollConnectionManager::run() {
    epoll_event events[1024];
      
    while (true) {
        int n           = epoll_wait(epfd, events, 1024, 5000);
        double now      = getCurrentTimeMs(); // Maybe move this to clean up idle connections only

        for (int i = 0; i < n; i++) 
            handleEvent(events[i]);
        cleanupIdleConnections(now);
    }
}

// =====================================================================
// 	CONNECTION MANAGER EVENT HANDLING
// =====================================================================

void EpollConnectionManager::handleEvent(epoll_event &ev) {

    int fd          = ev.data.fd;
    Socket *sock    = listeningSockets.find(fd) != listeningSockets.end() ? listeningSockets[fd] : NULL;
    
    if (sock) handleNewConnection(sock);
    else if (ev.events & EPOLLIN && isPipeEvent(fd)) handlePipeResponse(fd); 
    else if (ev.events & EPOLLIN) handleRead(fd);
    else if (ev.events & EPOLLOUT) handleWrite(fd);
}

void EpollConnectionManager::handleNewConnection(Socket *sock) {
    int         connfd;
    
    EventLog::log(NEW_CONNECTION, sock->getFd());
    while ((connfd = sock->acceptConnection()) > 0) {
        makeNonBlocking(connfd);
        setInstance(connfd, EPOLLIN , EPOLL_CTL_ADD);
        connections[connfd].fd = connfd;
        connections[connfd].keepAlive = false;
        connections[connfd].lastActive = getCurrentTimeMs();
        EventLog::log(EPOLL_ADD_CONNECTION, connfd);
    }
    if (errno != EAGAIN && errno != EWOULDBLOCK)
        perror("accept");
}

void EpollConnectionManager::badRequest(const int fd) {

    EventLog::log(EPOLL_EVENT_ERROR, fd);
    connections[fd].readBuffer.clear();
    std::ostringstream oss;
    oss << connections[fd].request.getErrorCode();
    // This wont be here
    connections[fd].writeBuffer =   "HTTP/1.1 " + oss.str() + " Bad Request\r\n"
                                    "Content-Length: 0\r\n"
                                    "Connection: close\r\n"
                                    "\r\n";
                                    
    setInstance(fd, EPOLLOUT, EPOLL_CTL_MOD);
}

void EpollConnectionManager::successRequest(const int fd) {

    EventLog::log(EPOLL_EVENT_SUCCESS, fd);
    connections[fd].readBuffer.clear();
    std::ostringstream oss;
    oss << 200;
    ServerResponse sRes = connections[fd].response.sres;
    connections[fd].writeBuffer =   "HTTP/1.1 ";


    connections[fd].writeBuffer =   "HTTP/1.1 200 Success\r\n"
                                    "Content-Length: 0\r\n"
                                    "Connection: close\r\n"
                                    "\r\n";
    setInstance(fd, EPOLLOUT, EPOLL_CTL_MOD);
}


void EpollConnectionManager::requestHandler(const int clientfd) {
    std::cout << "Handling request for client fd: " << clientfd << std::endl;
    std::cout << "Request Method: " << connections[clientfd].request.getControlData().method << std::endl;
    std::cout << "Error Code: " << connections[clientfd].request.getErrorCode() << std::endl;
    if (connections[clientfd].request.getHeaders().has("Connection")) {
        std::string connHeader = connections[clientfd].request.getHeaders().get("Connection");
        if (connHeader == "close")
            connections[clientfd].keepAlive = false;
    }
    if (connections[clientfd].request.getErrorCode() != 0)
        badRequest(clientfd);
    else 
    {
        connections[clientfd].response = serverManager.handleRequest(connections[clientfd].request);
        if (connections[clientfd].response.pathToCgi != "")
             CGIHandler(clientfd, connections[clientfd].response.pathToCgi);
        else
        {
            connections[clientfd].writeBuffer = connections[clientfd].response.sres.to_string();
            setInstance(clientfd, EPOLLOUT, EPOLL_CTL_MOD); // here is that we try to hook the server part.
        }
    }
}

#define MAX_REQ_LINE_LENGTH     40                      // 4 KB
#define MAX_HEADER_SIZE         65536                   // 64 KB
#define MAX_BODY_SIZE           (100 * 1024 * 1024)     // 100 MB
#define MAX_CHUNK_SIZE          (8 * 1024 * 1024)       // 8 MB
#define MAX_REQ_TIMEOUT         15000                   // 15 seconds

#define NONE_DONE               0
#define CONTROL_DATA_DONE       1 << 0
#define HEADERS_DONE            1 << 2
#define BODY_DONE               1 << 3            

// =====================================================================
// 	HANDLE READ EVENT
// =====================================================================

void EpollConnectionManager::handleRead(int clientfd) {
    Connection  &conn = connections[clientfd];
    char        buffer[MAX_REQ_LINE_LENGTH];
    int         bytesRead;
    int         totalBytesRead = 0;
    int         state = NONE_DONE;
    
    EventLog::log(EPOLL_EVENT_READING, clientfd);

    while ((bytesRead = read(clientfd, buffer, MAX_REQ_LINE_LENGTH)) > 0)
    {
        std::cout << "Error code before validation: " << conn.request.getErrorCode() << std::endl;
        if (conn.request.getErrorCode() != 0)
        {

            badRequest(clientfd);
            return;
        }
        if (bytesRead == -1 || bytesRead == 0)
        {
            conn.request.setErrorCode(400);
            badRequest(clientfd);
            return;
        }

        std::string buf = std::string(buffer, bytesRead);
        conn.scanner.append(buf);
        totalBytesRead += bytesRead;

        if (NONE_DONE == state++)
        {
            std::cout << "state "<< state << std::endl;
            validateRequestParts(conn.scanner, state, conn.request);
            std::cout << "Error code after validation: " << conn.request.getErrorCode() << std::endl;
            if (conn.request.getErrorCode() != 0)
            {
                badRequest(clientfd);
                return;
            }
        }
        if (state == CONTROL_DATA_DONE && totalBytesRead >= MAX_HEADER_SIZE)
        {
            conn.request.setErrorCode(400);
            badRequest(clientfd);
            return;
        }
        if (state == CONTROL_DATA_DONE && buf.find("\r\n\r\n") != std::string::npos)
        {
            state = HEADERS_DONE;
            validateRequestParts(conn.scanner, state, conn.request);
            if (conn.request.getErrorCode() != 0)
            {
                badRequest(clientfd);
                return;
            }
        }
        if (state == HEADERS_DONE)
        { 
            if (conn.request.getHeaders().has("Content-Length")) 
            {
                std::string contentLength       = conn.request.getHeaders().get("Content-Length");
                int contentLengthInt            = atoi_safe(contentLength);
                size_t bodyStart                = conn.request.getControlData().size + conn.request.getHeaders().getSize();
                size_t bodyBytesAvailable       = conn.scanner.getSize() - bodyStart;

                if (bodyBytesAvailable < static_cast<unsigned long>(contentLengthInt))
                    continue;
                else if (bodyBytesAvailable == static_cast<unsigned long>(contentLengthInt))
                    validateRequestParts(conn.scanner, state, conn.request);
                else
                {
                    badRequest(clientfd);
                    return;
                }
                
            }
        }
        
    }

    if (bytesRead == 0)
        closeConnection(clientfd);
    if (state < 2)
    {
        badRequest(clientfd);
        return;
    }
    requestHandler(clientfd);
}

void EpollConnectionManager::handleWrite(int clientfd) {
    Connection &conn = connections[clientfd];
    int bytesSent = write(clientfd, conn.writeBuffer.data(), conn.writeBuffer.size());
    if (bytesSent > 0) conn.writeBuffer.erase(0, bytesSent);

    if (conn.writeBuffer.empty()) {
        if (conn.keepAlive) {
            setInstance(clientfd, EPOLLIN, EPOLL_CTL_MOD);
            connections[clientfd].lastActive = getCurrentTimeMs();
            conn.readBuffer.clear();
        } else
            closeConnection(clientfd);
    }
}

// =====================================================================
// 	IDDLE CONNECTION CLEANUP
// =====================================================================
void EpollConnectionManager::cleanupIdleConnections(const double &now) { 
    const int TIMEOUT_MS = 1000;
    
    for (ConnectionIterator it = connections.begin(); it != connections.end();) {
        ConnectionIterator toDelete = it;
        ++it;
        if (now - toDelete->second.lastActive > TIMEOUT_MS)
            closeConnection(toDelete->first);
    }
}

// =====================================================================
// 	CLOSE CONNECTION
// Node.js wont close without shutting down connections check if valid
// =====================================================================
void EpollConnectionManager::closeConnection(int fd) {
    EventLog::log(EPOLL_EVENT_CLOSE, fd);
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    shutdown(fd, SHUT_RDWR);
    close(fd);
    connections.erase(fd);
    // TODO: erase pipes asociated with client on close
}

void EpollConnectionManager::CGIHandler(const int fd, const std::string& path)
{

    std::cout << path;
    const char* cgiPath = "/home/capapes/Desktop/webserver/cgiTest.py";
	int pipefd[2];

	pipe(pipefd);
	makeNonBlocking(pipefd[0]);
    std::cout << "\n\nhandle pipe creation" << std::endl;
	pid_t pid = fork();
    if (pid == -1)
    {
        // [TODO] send error message to client
        std::cout << "Fork failed" << std::endl;
        return;
    }

    if (pid != 0) {
        setInstance(pipefd[0], EPOLLIN, EPOLL_CTL_ADD);
	    pipeToClient[pipefd[0]] = fd;
    }
	if (pid == 0) {
        // [TODO] send environment variables
		dup2(pipefd[1], STDOUT_FILENO);

		close(pipefd[0]);
		close(pipefd[1]);

		execl(cgiPath, cgiPath, (char*)NULL);
         std::cout << "Execl failed" << std::endl;
		_exit(1);
	}
    
	close(pipefd[1]);

	waitpid(pid, NULL, WNOHANG);
}

bool EpollConnectionManager::isPipeEvent(int fd)
{
    return (pipeToClient.find(fd) != pipeToClient.end());
}

void EpollConnectionManager::handlePipeResponse(int fd)
{
    char    buf[4096];
    int     bytesRead;
    std::string  readBuffer;

    std::cout << "handle pipe response" << std::endl;
    EventLog::log(EPOLL_EVENT_READING, fd);
    while ((bytesRead = read(fd, buf, sizeof(buf))) > 0)
        readBuffer.append(buf, bytesRead);
    if (bytesRead == 0)
    {
        // Delete pipe register
        EventLog::log(EPOLL_EVENT_CLOSE, fd);
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
        close(fd);
        pipeToClient.erase(fd);
        // send error to client
    }
    int clientFd = pipeToClient[fd];
    EventLog::log(EPOLL_EVENT_SUCCESS, clientFd);
    connections[clientFd].readBuffer.clear();
    std::ostringstream oss;
    oss << 200;
    connections[clientFd].writeBuffer = readBuffer;
    setInstance(clientFd, EPOLLOUT, EPOLL_CTL_MOD);

    // Delete pipe register
    EventLog::log(EPOLL_EVENT_CLOSE, fd);
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    close(fd);
    pipeToClient.erase(fd);
}