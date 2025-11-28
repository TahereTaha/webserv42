/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:23:08 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 09:53:48 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"
#include <sys/epoll.h>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <ctime>    
#include <sys/time.h> 
#include "../http_request_parser/Request.hpp"


struct Connection {
    int          fd;
    std::string  readBuffer;
    Request      request;
    std::string  writeBuffer;
    bool         keepAlive;
    double       lastActive;
};

typedef std::map<int, Connection>::iterator ConnectionIterator;

class EpollConnectionManager {
    public:
        EpollConnectionManager(std::map<int, Socket*>);

    private:
        int epfd;
        std::map<int, Socket*> listeningSockets;
        std::map<int, Connection> connections;

        void run();
        void setInstance(int fd, uint32_t events, int op);
        void handleNewConnection(Socket *sock);
        void handleEvent(epoll_event &ev);
        void handleRead(int clientfd);
        void handleWrite(int clientfd);
        void cleanupIdleConnections(const double &now);
        void closeConnection(int fd);
        // Request handler things
        void badRequest(const int fd);
        void successRequest(const int fd);
        void requestHandler(const int clientfd);
        void exitWithError(const std::string& message);
};
