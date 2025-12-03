#include <setUpSockets.hpp>
#include "EpollConnectionManager.hpp"
#include "Socket.hpp"
#include <iostream>
#include "Log.hpp"
#include <set>

#include <intermediate_representation.hpp>

#include <cstring>

static std::vector<struct sockaddr_storage>	add_socket(std::vector<struct sockaddr_storage> sockets, struct sockaddr_storage socket)
{
	size_t	socket_size;
	if (socket.ss_family == AF_INET)
		socket_size = sizeof(sockaddr_in);
	else
		socket_size = sizeof(sockaddr_in6);
	
	size_t	i = 0;
	while (i < sockets.size())
	{
		if (!std::memcmp(&sockets[i], &socket, socket_size))
			return (sockets);
		i++;
	}
	sockets.push_back(socket);
	return (sockets);
}

static std::vector<struct sockaddr_storage>	add_sockets(std::vector<struct sockaddr_storage> sockets, std::vector<struct sockaddr_storage> new_sockets)
{
	size_t	i = 0;
	while (i < new_sockets.size())
	{
		sockets = add_socket(sockets, new_sockets[i]);
		i++;
	}
	return (sockets);
}

static std::vector<struct sockaddr_storage>	get_distict_sockets(std::vector<t_server> servers)
{
	std::vector<struct sockaddr_storage> diferent_sockets;
	
	size_t	i = 0;
	while (i < servers.size())
	{
		diferent_sockets = add_sockets(diferent_sockets, servers[i].socket);
		i++;
	}
	return (diferent_sockets);
}

std::map<int, Socket *>	set_up_sockets(std::vector<t_server> servers)
{
	std::vector<struct sockaddr_storage> diferent_sockets = get_distict_sockets(servers);

	std::map<int, Socket*>	listeningSockets;
	size_t	i = 0;
	while (i < diferent_sockets.size())
	{
		Socket	*socket = new Socket(diferent_sockets[i]);
		listeningSockets[socket->getFd()] = socket;
		i++;
	}
	return (listeningSockets);
}

//int main() {
//    try {
//        EventLog::init("event.log");
//
//        int ports[] = {8080, 8081, 8082}; // Example ports
//        std::map<int, Socket*> listeningSockets;
//
//        // to not allocate memory
//        Socket sock(ports[0]);
//        listeningSockets[sock.getFd()] = &sock;
//        Socket sock1(ports[1]);
//        listeningSockets[sock1.getFd()] = &sock1;
//        Socket sock2(ports[2]);
//        listeningSockets[sock2.getFd()] = &sock2;
//        
//        EpollConnectionManager manager(listeningSockets);
//        EventLog::shutdown();
//
//    } catch (const std::exception &ex) {
//        std::cerr << "Exception: " << ex.what() << "\n";
//        return 1;
//    }
//
//    return 0;
//}
