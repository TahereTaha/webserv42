/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:25:34 by capapes           #+#    #+#             */
/*   Updated: 2025/08/12 15:00:34 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EpollConnectionManager.hpp"
#include <stdlib.h>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include "Event.hpp"
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
    {
        std::cerr << "Error setting epoll instance for fd " << fd << ": " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
  
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
        std::cout << "Adding socket " << it->first << " to epoll\n";
        setInstance(it->first, EPOLLIN, EPOLL_CTL_ADD);
        std::ostringstream oss;
        oss << it->first;
        EventLog::log(EPOLL_ADD, "Added socket to epoll: " + oss.str());
    }

    run();
}

void EpollConnectionManager::run() {
    epoll_event events[1024];
      
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

void EpollConnectionManager::handleEvent(epoll_event &ev) {

    int fd          = ev.data.fd;
    Socket *sock    = listeningSockets.find(fd) != listeningSockets.end() ? listeningSockets[fd] : NULL;
    
    if (sock) handleNewConnection(sock);
    else if (ev.events & EPOLLIN) handleRead(fd);
    else if (ev.events & EPOLLOUT) handleWrite(fd);
}

void EpollConnectionManager::handleNewConnection(Socket *sock) {
    int         connfd;
    
    std::ostringstream oss;
    oss << sock->getFd();
    EventLog::log(NEW_CONNECTION, "Handling new connection on socket: " + oss.str());
    while ((connfd = sock->acceptConnection()) > 0) {
        makeNonBlocking(connfd);
        setInstance(connfd, EPOLLIN , EPOLL_CTL_ADD);
        connections[connfd].fd = connfd;
        connections[connfd].keepAlive = true;
        connections[connfd].lastActive = getCurrentTimeMs();
        std::ostringstream oss;
        oss << connfd;
        EventLog::log(EPOLL_ADD, "Added new connection to epoll: " + oss.str());
   }
    if (errno != EAGAIN && errno != EWOULDBLOCK)
        perror("accept");
}

void EpollConnectionManager::badRequest(int fd) {
    std::ostringstream oss;
    oss << fd;
    std::ostringstream oss2;
    oss2 << connections[fd].request.getErrorCode();
    EventLog::log(EPOLL_EVENT, "Request error for client " + oss.str() + ": " + oss2.str());
    connections[fd].readBuffer.clear();
    connections[fd].writeBuffer = "HTTP/1.1 " + std::to_string(connections[fd].request.getErrorCode()) + " Error\r\n\r\n";
    setInstance(fd, EPOLLOUT, EPOLL_CTL_MOD);
}

void EpollConnectionManager::handleRead(int clientfd) {
    char buf[4096];
    int bytesRead;

    std::ostringstream oss;
    oss << clientfd;
    EventLog::log(EPOLL_EVENT, "Handling read event for client: " + oss.str());
    while ((bytesRead = read(clientfd, buf, sizeof(buf))) > 0)
    {
        connections[clientfd].readBuffer.append(buf, bytesRead);
        connections[clientfd].lastActive = getCurrentTimeMs();
    }
    if (bytesRead == 0)
        closeConnection(clientfd);
    connections[clientfd].request = validateRequest(connections[clientfd].readBuffer);
    if (connections[clientfd].request.getErrorCode() != 0) 
        badRequest(clientfd);
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
    const int TIMEOUT_MS = 50000;
    
    for (ConnectionIterator it = connections.begin(); it != connections.end();) {
        ConnectionIterator toDelete = it;
        ++it;
        if (now - toDelete->second.lastActive > TIMEOUT_MS)
        {
            std::ostringstream oss;
            oss << toDelete->first;
            EventLog::log(EPOLL_EVENT, "Closing idle connection: " + oss.str());
            closeConnection(toDelete->first);
        }
    }
}

void EpollConnectionManager::closeConnection(int fd) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    close(fd);
    connections.erase(fd);
}
