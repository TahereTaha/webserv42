/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:25:34 by capapes           #+#    #+#             */
/*   Updated: 2025/11/29 17:32:16 by capapes          ###   ########.fr       */
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
    
    std::cout << "events" << fd << std::endl;
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

EpollConnectionManager::EpollConnectionManager(std::map<int, Socket*> socks) : epfd(-1), listeningSockets(socks) {
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
    connections[fd].writeBuffer =   "HTTP/1.1 400 Bad Request\r\n"
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
    connections[fd].writeBuffer =   "HTTP/1.1 200 Success\r\n"
                                    "Content-Length: 0\r\n"
                                    "Connection: close\r\n"
                                    "\r\n";
    setInstance(fd, EPOLLOUT, EPOLL_CTL_MOD);
}


void EpollConnectionManager::requestHandler(const int clientfd) {
    connections[clientfd].request = validateRequest(connections[clientfd].readBuffer);
    if (connections[clientfd].request.getHeaders().has("Connection")) {
        std::string connHeader = connections[clientfd].request.getHeaders().get("Connection");
        if (connHeader == "close")
            connections[clientfd].keepAlive = false;
    }
    if (connections[clientfd].request.getErrorCode() != 0)
    {
        badRequest(clientfd);
    }
    else if (connections[clientfd].request.getControlData().requestTarget == "/cgi")
        CGIHandler(clientfd, ".cgiTest.py");
    else 
        successRequest(clientfd); // here is that we try to hook the server part.
}

void EpollConnectionManager::handleRead(int clientfd) {
    char    buf[4096];
    int     bytesRead;

    EventLog::log(EPOLL_EVENT_READING, clientfd);
    while ((bytesRead = read(clientfd, buf, sizeof(buf))) > 0)
    {
        connections[clientfd].readBuffer.append(buf, bytesRead);
        connections[clientfd].lastActive = getCurrentTimeMs();
    }
    if (bytesRead == 0)
        closeConnection(clientfd);
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