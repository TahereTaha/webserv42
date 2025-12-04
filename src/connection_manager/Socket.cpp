/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:23:53 by capapes           #+#    #+#             */
/*   Updated: 2025/12/04 13:54:40 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <cstring>
#include <cerrno>     // for errno, EAGAIN, EWOULDBLOCK
#include <cstdio>     // for perror
#include "Log.hpp"
#include <sstream>



Socket::Socket(struct sockaddr_storage socket_addr) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	size_t	addr_len;
	if (socket_addr.ss_family == AF_INET)
		addr_len = sizeof(struct sockaddr_in);
	else
		addr_len = sizeof(struct sockaddr_in6);



    if (bind(fd, (struct sockaddr *)&socket_addr, addr_len) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(fd, SOMAXCONN) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    makeNonBlocking(fd);
    // EventLog::log(SOCKET_BIND, port);
    this->port = ntohs(((struct sockaddr_in *)&socket_addr)->sin_port);
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

int Socket::getPort() const {
    return port;
}
