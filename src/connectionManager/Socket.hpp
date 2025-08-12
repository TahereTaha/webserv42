/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:23:28 by capapes           #+#    #+#             */
/*   Updated: 2025/08/05 16:51:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

#define EXIT_FAILURE 1
void makeNonBlocking(int fd);

class Socket {
public:
    Socket(int port);
    ~Socket();

    int     getFd() const;
    int     acceptConnection();

private:
    int fd;
};

#endif
