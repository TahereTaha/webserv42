/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:23:28 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 20:13:33 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

#include <intermediate_representation.hpp>

#define EXIT_FAILURE 1
void makeNonBlocking(int fd);

class Socket {
public:
    Socket(struct sockaddr_storage socket_addr);
    ~Socket();

    int     getFd() const;
    int     getPort() const;
    int     acceptConnection();

private:
    int fd;
    int port;
};

#endif
