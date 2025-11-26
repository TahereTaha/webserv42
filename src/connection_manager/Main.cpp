/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:30:40 by capapes           #+#    #+#             */
/*   Updated: 2025/10/07 14:16:12 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EpollConnectionManager.hpp"
#include "Socket.hpp"
#include <iostream>
#include "Log.hpp"




int main() {
    try {
        EventLog::init("event.log");

        int ports[] = {8080, 8081, 8082}; // Example ports
        std::map<int, Socket*> listeningSockets;

        // to not allocate memory
        Socket sock(ports[0]);
        listeningSockets[sock.getFd()] = &sock;
        Socket sock1(ports[1]);
        listeningSockets[sock1.getFd()] = &sock1;
        Socket sock2(ports[2]);
        listeningSockets[sock2.getFd()] = &sock2;
        
        EpollConnectionManager manager(listeningSockets);
        EventLog::shutdown();

    } catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
