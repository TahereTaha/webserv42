/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:25:34 by capapes           #+#    #+#             */
/*   Updated: 2025/12/04 18:56:40 by capapes          ###   ########.fr       */
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
         // --- 2xx Success ---
        case 200: return "OK";
        case 201: return "Created";
        case 202: return "Accepted";
        case 204: return "No Content";

        // --- 3xx Redirection ---
        case 300: return "Multiple Choices";
        case 301: return "Moved Permanently";
        case 302: return "Found";
        case 303: return "See Other";
        case 304: return "Not Modified";
        case 305: return "Use Proxy";
        case 307: return "Temporary Redirect";
        case 308: return "Permanent Redirect";

        // --- 4xx Client Errors ---
        case 400: return "Bad Request";
        case 401: return "Unauthorized";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 408: return "Request Timeout";
        case 411: return "Length Required";
        case 413: return "Payload Too Large";
        case 414: return "URI Too Long";
        case 415: return "Unsupported Media Type";

        // --- 5xx Server Errors ---
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 502: return "Bad Gateway";
        case 503: return "Service Unavailable";
        case 504: return "Gateway Timeout";

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
    {
//        perror("epoll_ctl failed");
        return;
    }
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
        // EventLog::log(EPOLL_ADD_SOCKET, it->first);
        serverUpMessage(it->second->getPort());
    }
    run();
}
#define MAX_EVENTS 8192

void EpollConnectionManager::run()
{
    epoll_event events[MAX_EVENTS];
      
    while (true) {
        int n           = epoll_wait(epfd, events, 1024, 500);
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
    
    // EventLog::log(NEW_CONNECTION, sock->getFd());
    while ((connfd = sock->acceptConnection()) > 0) {
        makeNonBlocking(connfd);
        setInstance(connfd, EPOLLIN , EPOLL_CTL_ADD);
        // EventLog::log(EPOLL_ADD_CONNECTION, connfd);
        connections[connfd].fd = connfd;
        connections[connfd].keepAlive = false;
        connections[connfd].lastActive = getCurrentTimeMs();
    }
}

void EpollConnectionManager::badRequest(const int fd)
{
    // EventLog::log(EPOLL_EVENT_ERROR, fd);
    connections[fd].readBuffer.clear();
	
	connections[fd].response = serverManager.handleErrorRequest(connections[fd].request);
   	connections[fd].writeBuffer = connections[fd].response.sres.to_string();
    std::cout << connections[fd].writeBuffer;
//	int code = connections[fd].request.getErrorCode();
//	std::ostringstream oss;
//
//	oss << "HTTP/1.1 " << code << " " << getReasonPhrase(code) << "\r\n"
//		<< "Content-Length: 0\r\n"
//		<< "Connection: close\r\n"
//		<< "\r\n";
//
//	connections[fd].writeBuffer = oss.str();
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

    // EventLog::log(EPOLL_EVENT_READING, clientfd);
    while ((bytesRead = read(clientfd, buf, sizeof(buf))) > 0)
    {
        connections[clientfd].readBuffer.append(buf, bytesRead);
        connections[clientfd].lastActive = getCurrentTimeMs();
    }
    if (bytesRead == 0)
    {
        connections[clientfd].request.setErrorCode(500);
        badRequest(clientfd);
        return ;
    }
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
	//std::cout << "resd pipe" << std::endl;
    // EventLog::log(EPOLL_EVENT_READING, pipefd);

    while ((bytesRead = read(pipefd, buf, sizeof(buf))) > 0)
    {
        readBuffer.append(buf, bytesRead);
    }
    if (bytesRead == 0)
    {
        
    }
    //std::cout << readBuffer << std::endl;
    int CGIClient = findClientByPipe(pipefd);
	if (CGIClient == -1)
	{
		epoll_ctl(epfd, EPOLL_CTL_DEL, pipefd, NULL);
	}
    connections[CGIClient].readBuffer.clear();
    connections[CGIClient].writeBuffer = readBuffer;
    setInstance(CGIClient, EPOLLOUT, EPOLL_CTL_MOD);
    // EventLog::log(EPOLL_EVENT_SUCCESS, CGIClient);

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
        close(pipefd);
		return;
	}

    const std::string &body = CGIConn[CGIClient].data.body;

    size_t total = 0;
    while (total < body.size()) {
        ssize_t n = write(pipefd, body.data() + total, body.size() - total);
        if (n <= 0) {
            perror("write to CGI stdin");
            break;
        }
        total += n;
    }

    if (total == 0 && CGIConn[CGIClient].data.body.size() != 0)
    {
        connections[CGIClient].request.setErrorCode(500);
        badRequest(CGIClient);

    }
    close(pipefd);
	// CLEAN UP
	CGIConn[CGIClient].lastActive = getCurrentTimeMs();
    CGIConn[CGIClient].data.body.erase();
	CGIConn[CGIClient].stdIn = -1;
	epoll_ctl(epfd, EPOLL_CTL_DEL, pipefd, NULL);
}

// =====================================================================
// 	IDDLE CONNECTION CLEANUP
// =====================================================================
void EpollConnectionManager::cleanupIdleConnections(const double &now)
{ 
    const int TIMEOUT_MS = 1000;
    const int TIMEOUT_MS_SM = 500;
    
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
		if (now - toDelete->second.lastActive > TIMEOUT_MS_SM)
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
            connections[it->first].request.setErrorCode(500);
            badRequest(it->first);
			CGIConn.erase(it->first);
		}
	}
}

// =====================================================================
// 	CLOSE CONNECTION
//  Node.js wont close without shutting down connections check if valid
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
	// EventLog::log(EPOLL_EVENT_CLOSE, fd);
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
inline void addEnv(std::map<std::string, std::string> &env,
                   const std::string &key,
                   const std::string &value)
{
    env[key] = value;
}

CgiData prepareCgiEnvironment(const Request &req, const std::string &scriptPath)
{
    CgiData data;

    // IMPORTANT: use data.envStrings, not a local vector
    std::map< std::string, std::string> &env = data.envStrings;

    addEnv(env, "GATEWAY_INTERFACE", "CGI/1.1");
    addEnv(env, "SERVER_PROTOCOL",  "HTTP/1.1");
    addEnv(env, "REQUEST_METHOD",   req.getControlData().method);
    addEnv(env, "SCRIPT_FILENAME",  scriptPath);
    addEnv(env, "SCRIPT_NAME",      scriptPath);
    addEnv(env, "REQUEST_URI",      req.getControlData().requestTarget);

    Headers headers = req.getHeaders();

    if (headers.has("Content-Length"))
        addEnv(env, "CONTENT_LENGTH", headers.get("Content-Length"));

    if (headers.has("Content-Type"))
        addEnv(env, "CONTENT_TYPE", headers.get("Content-Type"));

    // Add remaining headers as HTTP_* (avoid duplicates)
    for (Headers::iterator it = headers.begin(); it != headers.end(); ++it)
    {
        const std::string &key   = it->first;
        const std::string &value = it->second;

        if (key == "Content-Length" || key == "Content-Type")
            continue;

        std::string envKey = "HTTP_" + key;
        std::replace(envKey.begin(), envKey.end(), '-', '_');
        std::transform(envKey.begin(), envKey.end(), envKey.begin(), ::toupper);

        addEnv(env, envKey, value);
    }

    data.body = req.getBody();
    return data;
}

// =====================================================================
// 		CGI Handler
// =====================================================================
void EpollConnectionManager::CGIHandler(const int fd, const std::string& path)
{
  std::cout << "im CGI handler" << path<< std::endl;
    const char* cgiPath = path.c_str();
	int pipe_stdout[2];
	int pipe_stdin[2];

	pipe(pipe_stdout);
	pipe(pipe_stdin);
	makeNonBlocking(pipe_stdout[0]);
    makeNonBlocking(pipe_stdin[1]);
    CGIConn[fd].data = prepareCgiEnvironment(connections[fd].request, path);
    CGIConn[fd].stdOut = pipe_stdout[0];
    CGIConn[fd].stdIn = pipe_stdin[1];
    CGIConn[fd].lastActive = getCurrentTimeMs();

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
    if (pid != 0) {
		setInstance(pipe_stdin[1], EPOLLOUT, EPOLL_CTL_ADD);
        setInstance(pipe_stdout[0], EPOLLIN, EPOLL_CTL_ADD);
    }
	if (pid == 0)
	{
	  
		
		dup2(pipe_stdout[1], STDOUT_FILENO);
    	dup2(pipe_stdin[0], STDIN_FILENO);

		close(pipe_stdout[0]);
		close(pipe_stdout[1]);
		close(pipe_stdin[0]);
		close(pipe_stdin[1]);

        // Prepare envp
         // Set CGI environment variables
        for (std::map<std::string,std::string>::iterator it = CGIConn[fd].data.envStrings.begin();
            it != CGIConn[fd].data.envStrings.end(); ++it)
        {
		// std::cerr << "this is it first: " << it->first << std::endl;
		// std::cerr << "this is it second: " << it->second << std::endl;
        setenv(it->first.c_str(), it->second.c_str(), 1);
        }



		execl(cgiPath, cgiPath, (char*)NULL);
		std::ostringstream oss;
		oss << "HTTP/1.1 " << 500 << " " << getReasonPhrase(500) << "\r\n"
			<< "Content-Length: 0\r\n"
			<< "Connection: close\r\n"
			<< "\r\n";

		std::cout << oss.str() << std::endl;
        std::cerr << "exit" << std::endl;
		exit (1);
	}
    
	close(pipe_stdout[1]);
	close(pipe_stdin[0]);
	waitpid(pid, NULL, WNOHANG);
}







