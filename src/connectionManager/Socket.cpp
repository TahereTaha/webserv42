/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:23:53 by capapes           #+#    #+#             */
/*   Updated: 2025/10/06 19:03:35 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <cstring>
#include <cerrno>     // for errno, EAGAIN, EWOULDBLOCK
#include <cstdio>     // for perror
#include "Event.hpp"
#include <sstream>

Socket::Socket(int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(fd, SOMAXCONN) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    makeNonBlocking(fd);
    EventLog::log(SOCKET_BIND, port);
}

Socket::~Socket() {
    close(fd);
}

int Socket::getFd() const {
    return fd;
}

void makeNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int Socket::acceptConnection() {
    sockaddr_in cli;
    memset(&cli, 0, sizeof(cli));
    socklen_t   clilen = sizeof(cli);
    
    return accept(fd, (sockaddr*)&cli, &clilen);
}
