/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:25:34 by capapes           #+#    #+#             */
/*   Updated: 2025/12/03 19:32:12 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EpollConnectionManager.hpp"

// =====================================================================
// 	        MESSAGES AND NON CLASS UTILS
// =====================================================================
void serverUpMessage(int port)
{
    std::cout << COLOR_GREEN << "✔ Server up and running "
      << COLOR_CYAN   << "on port "
      << COLOR_YELLOW << port
      << COLOR_RESET  << std::endl;
}

double getCurrentTimeMs()
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (static_cast<double>(tv.tv_sec) * 1000.0) +
           (static_cast<double>(tv.tv_usec) / 1000.0);
}

std::string getReasonPhrase(int code) {
    switch (code) {
        case 400: return "Bad Request";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 411: return "Length Required";
        case 413: return "Payload Too Large";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        default:  return "Unknown";
    }
}

// =====================================================================
//       UTILS
// =====================================================================

void EpollConnectionManager::setInstance(int fd, uint32_t events, int op)
{
    epoll_event ev;
    
    memset(&ev, 0, sizeof(ev));
    ev.events = events | EPOLLET;
    ev.data.fd = fd;

    if (epoll_ctl(epfd, op, fd, &ev) == -1)
        exitWithError("Failed to set epoll instance");
}

void EpollConnectionManager::exitWithError(const std::string& message)
{
    std::cerr << COLOR_RED << "✘ " << message << COLOR_RESET << std::endl;
    exit(EXIT_FAILURE);
}

bool EpollConnectionManager::isClient(int fd)
{
    return (connections.find(fd) != connections.end());
}

int EpollConnectionManager::findClientByPipe(int pipefd)
{
    for (CGIIterator it = CGIConn.begin(); it != CGIConn.end();)
    {
        if (it->second.stdIn  == pipefd ||
            it->second.stdOut == pipefd)
        {
            return it->first;
        }
		it++;
    }

    return -1;
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
        EventLog::log(EPOLL_ADD_SOCKET, it->first);
        serverUpMessage(it->second->getPort());
    }
    run();
}
#define MAX_EVENTS 8192

void EpollConnectionManager::run()
{
    epoll_event events[MAX_EVENTS];
      
    while (true) {
        int n           = epoll_wait(epfd, events, 1024, 5000);
        double now      = getCurrentTimeMs();

        for (int i = 0; i < n; i++) 
            handleEvent(events[i]);
        cleanupIdleConnections(now);
    }
}

// =====================================================================
// 	CONNECTION MANAGER EVENT HANDLING
// =====================================================================

void EpollConnectionManager::handleEvent(epoll_event &ev)
{
    int fd          = ev.data.fd;
    Socket *sock    = listeningSockets.find(fd) != listeningSockets.end() ? listeningSockets[fd] : NULL;
    
    if (sock) handleNewConnection(sock);
    else if (ev.events & EPOLLIN && isClient(fd)) handleRead(fd);
    else if (ev.events & EPOLLOUT && isClient(fd)) handleWrite(fd);
    else if (ev.events & EPOLLIN) handlePipeRead(fd);
	else handlePipeWrite(fd);
}

void EpollConnectionManager::handleNewConnection(Socket *sock)
{
    int         connfd;
    
    EventLog::log(NEW_CONNECTION, sock->getFd());
    while ((connfd = sock->acceptConnection()) > 0) {
        makeNonBlocking(connfd);
        setInstance(connfd, EPOLLIN , EPOLL_CTL_ADD);
        EventLog::log(EPOLL_ADD_CONNECTION, connfd);
        connections[connfd].fd = connfd;
        connections[connfd].keepAlive = false;
        connections[connfd].lastActive = getCurrentTimeMs();
    }
    if (errno != EAGAIN && errno != EWOULDBLOCK)
        perror("accept");
}

void EpollConnectionManager::badRequest(const int fd)
{
    EventLog::log(EPOLL_EVENT_ERROR, fd);
    connections[fd].readBuffer.clear();
    int code = connections[fd].request.getErrorCode();
	std::ostringstream oss;

	oss << "HTTP/1.1 " << code << " " << getReasonPhrase(code) << "\r\n"
		<< "Content-Length: 0\r\n"
		<< "Connection: close\r\n"
		<< "\r\n";

	connections[fd].writeBuffer = oss.str();
    setInstance(fd, EPOLLOUT, EPOLL_CTL_MOD);
}

void EpollConnectionManager::requestHandler(const int clientfd)
{
	connections[clientfd].request = validateRequest(connections[clientfd].readBuffer);
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
		std::cout << "\t\tthe path to the cgi is: " << connections[clientfd].response.pathToCgi << std::endl;
        if (connections[clientfd].response.pathToCgi != "")
			CGIHandler(clientfd, connections[clientfd].response.pathToCgi);
        else
        {
            connections[clientfd].writeBuffer = connections[clientfd].response.sres.to_string();
            setInstance(clientfd, EPOLLOUT, EPOLL_CTL_MOD); 
        }
    }
}

void EpollConnectionManager::handleRead(int clientfd)
{
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

void EpollConnectionManager::handleWrite(int clientfd)
{
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

void EpollConnectionManager::handlePipeRead(int pipefd)
{
    char    		buf[4096];
    int     		bytesRead;
    std::string  	readBuffer;

    EventLog::log(EPOLL_EVENT_READING, pipefd);
    while ((bytesRead = read(pipefd, buf, sizeof(buf))) > 0)
        readBuffer.append(buf, bytesRead);
    int CGIClient = findClientByPipe(pipefd);
	if (CGIClient == -1)
	{
		epoll_ctl(epfd, EPOLL_CTL_DEL, pipefd, NULL);
		return;
	}
    connections[CGIClient].readBuffer.clear();
    connections[CGIClient].writeBuffer = readBuffer;

    setInstance(CGIClient, EPOLLOUT, EPOLL_CTL_MOD);
    EventLog::log(EPOLL_EVENT_SUCCESS, CGIClient);

	// CLEAN UP
    CGIConn[CGIClient].stdOut = -1;
	epoll_ctl(epfd, EPOLL_CTL_DEL, pipefd, NULL);
	close(pipefd);
	CGIConn.erase(CGIClient);
}

void EpollConnectionManager::handlePipeWrite(int pipefd)
{
	int CGIClient = findClientByPipe(pipefd);
	if (CGIClient == -1)
	{
		epoll_ctl(epfd, EPOLL_CTL_DEL, pipefd, NULL);
		return;
	}
    int bytesSent = write(pipefd, CGIConn[CGIClient].data.body.c_str(), CGIConn[CGIClient].data.body.size());
    if (bytesSent > 0) CGIConn[CGIClient].data.body.erase(0, bytesSent);
	CGIConn[CGIClient].lastActive = getCurrentTimeMs();

	// CLEAN UP
    CGIConn[CGIClient].data.body.erase();
	CGIConn[CGIClient].stdIn = -1;
	epoll_ctl(epfd, EPOLL_CTL_DEL, pipefd, NULL);
	close(pipefd);
}

// =====================================================================
// 	IDDLE CONNECTION CLEANUP
// =====================================================================
void EpollConnectionManager::cleanupIdleConnections(const double &now)
{ 
    const int TIMEOUT_MS = 1000;
    
    for (ConnectionIterator it = connections.begin(); it != connections.end();) {
        ConnectionIterator toDelete = it;
        ++it;
        if (now - toDelete->second.lastActive > TIMEOUT_MS)
            closeConnection(toDelete->first);
    }
	for (CGIIterator it = CGIConn.begin(); it != CGIConn.end();)
	{
		CGIIterator toDelete = it;
		++it;
		if (now - toDelete->second.lastActive > TIMEOUT_MS)
        {
			if (it->second.stdIn != -1)
			{
				epoll_ctl(epfd, EPOLL_CTL_DEL, it->second.stdIn, NULL);
				close(it->second.stdIn);
				it->second.stdIn = -1;
			}
			if (it->second.stdOut != -1)
			{
				epoll_ctl(epfd, EPOLL_CTL_DEL, it->second.stdOut, NULL);
				close(it->second.stdOut);
				it->second.stdOut = -1;
			}
			CGIConn.erase(it->first);
		}
	}
}

// =====================================================================
// 	CLOSE CONNECTION
// Node.js wont close without shutting down connections check if valid
// =====================================================================

std::vector<int> getPipesForClient(int clientFd,
    const std::map<int, int> &pipeToClient)
{
    std::vector<int> pipes;

    for (std::map<int, int>::const_iterator it = pipeToClient.begin();
		it != pipeToClient.end(); ++it)
    {
        if (it->second == clientFd)
			pipes.push_back(it->first);
    }

    return pipes;
}

void EpollConnectionManager::closeConnection(int fd)
{
	EventLog::log(EPOLL_EVENT_CLOSE, fd);
	epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
	shutdown(fd, SHUT_RDWR);
	close(fd);
	connections.erase(fd);
	if (CGIConn.find(fd) != CGIConn.end())
	{
		if (CGIConn[fd].stdIn != -1)
		{
			epoll_ctl(epfd, EPOLL_CTL_DEL, CGIConn[fd].stdIn, NULL);
			close(CGIConn[fd].stdIn);
			CGIConn[fd].stdIn = -1;
		}
		if (CGIConn[fd].stdOut != -1)
		{
			epoll_ctl(epfd, EPOLL_CTL_DEL, CGIConn[fd].stdOut, NULL);
			close(CGIConn[fd].stdOut);
			CGIConn[fd].stdOut = -1;
		}
		CGIConn.erase(fd);
	}
}
// =====================================================================
// 		CGI utils
// =====================================================================

inline void addEnv(std::vector<std::string> &envStrings,
                   const std::string &key,
                   const std::string &value)
{
    envStrings.push_back(key + "=" + value);
}

CgiData prepareCgiEnvironment(const Request &req, const std::string &scriptPath)
{
    CgiData data;
    std::vector<std::string> envStrings;

    addEnv(envStrings, "GATEWAY_INTERFACE", "CGI/1.1");
    addEnv(envStrings, "SERVER_PROTOCOL", "HTTP/1.1");
    addEnv(envStrings, "REQUEST_METHOD", req.getControlData().method);
    addEnv(envStrings, "SCRIPT_FILENAME", scriptPath);
    addEnv(envStrings, "SCRIPT_NAME", scriptPath);
    addEnv(envStrings, "REQUEST_URI", req.getControlData().requestTarget);

	Headers headers = req.getHeaders();

    if (headers.has("Content-Length"))
        addEnv(envStrings, "CONTENT_LENGTH", headers.get("Content-Length"));
    else
        addEnv(envStrings, "CONTENT_LENGTH", "0");

    if (headers.has("Content-Type"))
        addEnv(envStrings, "CONTENT_TYPE", headers.get("Content-Type"));

    if (headers.has("Host"))
        addEnv(envStrings, "HTTP_HOST", headers.get("Host"));

    for (Headers::iterator it = headers.begin(); it != headers.end(); ++it)
	{
		const std::string &key   = it->first;
		const std::string &value = it->second;

		std::cout << key << ": " << value << std::endl;
	}

    data.body = req.getBody();

    for (size_t i = 0; i < envStrings.size(); ++i)
        data.envp.push_back(const_cast<char*>(envStrings[i].c_str()));

    data.envp.push_back(0);

    return data;
}

// =====================================================================
// 		CGI Handler
// =====================================================================
void EpollConnectionManager::CGIHandler(const int fd, const std::string& path)
{
    std::cout << path;
    const char* cgiPath = path.c_str(); // Change this to path
	int pipe_stdout[2];
	int pipe_stdin[2];

	pipe(pipe_stdout);
	pipe(pipe_stdin);
	makeNonBlocking(pipe_stdout[0]);
	makeNonBlocking(pipe_stdin[1]);
	pid_t pid = fork();
    if (pid == -1)
    {
        connections[fd].request.setErrorCode(500);
		close(pipe_stdout[0]);
		close(pipe_stdout[1]);
		close(pipe_stdin[0]);
		close(pipe_stdin[1]);
        badRequest(fd);
        return ;
    }
	CGIConn[fd].data = prepareCgiEnvironment(connections[fd].request, path);
	CGIConn[fd].stdOut = pipe_stdout[0];
	CGIConn[fd].stdIn = pipe_stdin[1];
	CGIConn[fd].lastActive = getCurrentTimeMs();
    if (pid != 0) {
		setInstance(pipe_stdin[1], EPOLLOUT, EPOLL_CTL_ADD);
        setInstance(pipe_stdout[0], EPOLLIN, EPOLL_CTL_ADD);
    }
	if (pid == 0)
	{
		char* args[2];
		args[0] = const_cast<char*>(cgiPath);
		args[1] = 0;   
		
		dup2(pipe_stdout[1], STDOUT_FILENO);
    	dup2(pipe_stdin[0], STDIN_FILENO);

		close(pipe_stdout[0]);
		close(pipe_stdout[1]);
		close(pipe_stdin[0]);
		close(pipe_stdin[1]);

		execve(cgiPath, args, &CGIConn[fd].data.envp[0]);
		std::ostringstream oss;
		oss << "HTTP/1.1 " << 500 << " " << getReasonPhrase(500) << "\r\n"
			<< "Content-Length: 0\r\n"
			<< "Connection: close\r\n"
			<< "\r\n";

		std::cout << oss.str() << std::endl;
		exit (1);
	}
    
	close(pipe_stdout[1]);
	close(pipe_stdin[0]);
	waitpid(pid, NULL, WNOHANG);
}







