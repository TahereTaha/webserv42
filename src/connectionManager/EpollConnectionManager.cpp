/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:25:34 by capapes           #+#    #+#             */
/*   Updated: 2025/10/07 14:53:24 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EpollConnectionManager.hpp"
#include <stdlib.h>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include "Log.hpp"
#include "ErrorHandler.hpp"
#include "../http_request_parser/Schemas.hpp"

// =====================================================================
// 	UTILITIES
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
        exit(EXIT_FAILURE);
  
}

// =====================================================================
// 	CONNECTION MANAGER CONSTRUCTOR
// =====================================================================

EpollConnectionManager::EpollConnectionManager(std::map<int, Socket*> socks) : epfd(-1) {
    if (socks.empty())
        return;
    
    epfd = epoll_create1(0);
    if (epfd == -1)
        exit(EXIT_FAILURE);
    listeningSockets = socks;
    for (std::map<int, Socket*>::iterator it = listeningSockets.begin(); it != listeningSockets.end(); ++it)
    {
        setInstance(it->first, EPOLLIN, EPOLL_CTL_ADD);
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
        connections[connfd].keepAlive = true;
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
    // oss << connections[fd].request.getErrorCode();
    oss << 200;
    connections[fd].writeBuffer = "HTTP/1.1 " + oss.str() + " Success\r\n\r\n";
    setInstance(fd, EPOLLOUT, EPOLL_CTL_MOD);
}

// void EpollConnectionManager::requestHandler(const int clientfd) {
    // Placeholder for request handling logic
    // connections[clientfd].request = validateRequest(connections[clientfd].readBuffer);
    // if (connections[clientfd].request.getErrorCode() != 0) 
    //     badRequest(clientfd);
    
// }

void EpollConnectionManager::handleRead(int clientfd) {
    char buf[4096];
    int bytesRead;

    EventLog::log(EPOLL_EVENT_READING, clientfd);
    while ((bytesRead = read(clientfd, buf, sizeof(buf))) > 0)
    {
        connections[clientfd].readBuffer.append(buf, bytesRead);
        connections[clientfd].lastActive = getCurrentTimeMs();
    }
    if (bytesRead == 0)
        closeConnection(clientfd);
    // requestHandler(clientfd);
    // temporary
    badRequest(clientfd);
    // closeConnection(clientfd);
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

void EpollConnectionManager::closeConnection(int fd) {
    EventLog::log(EPOLL_EVENT_CLOSE, fd);
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    close(fd);
    connections.erase(fd);
}
