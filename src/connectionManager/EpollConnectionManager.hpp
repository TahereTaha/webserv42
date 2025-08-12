/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:23:08 by capapes           #+#    #+#             */
/*   Updated: 2025/08/07 12:03:17 by capapes          ###   ########.fr       */
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
#include <ctime>    // for time_t and time()
#include <sys/time.h> // for gettimeofday() if you need milliseconds

struct Connection {
    int          fd;
    std::string  readBuffer;
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
};
