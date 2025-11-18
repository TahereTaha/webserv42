#include <IR_printing_functions.hpp>

#include <string>
#include <vector>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

static void	print_tab_level(size_t tab_level)
{
	while (tab_level)
	{
		std::cout << "\t";
		i--;
	}
}

std::string	getHTTPMethodSring(t_http_method method)
{
	if (method == GET)
		return ("GET");
	if (method == POST)
		return ("POST");
	if (method == DELETE)
		return ("DELETE");
	return ("");
}

std::string	getResponseTypeSring(t_response_type type)
{
	if (type == DEFAULT)
		return ("default");
	if (type == STATIC)
		return ("static");
	return ("");
}

//void	printStaticResponse(t_static_response static_response);
//void	printRedirectResponse(t_redirect_response redirect_response);
//void	printDefaultResponse(t_default_response default_response);
//void	printRoute(t_route route);

//static void	print_ipv6(char *data_storage)
//{
//	uint16_t *data = (uint16_t *)data_storage;
//
//	size_t	i = 0;
//	while (i < 8)
//	{
//		printf("%x", ntohs(data[i]));
//		i++;
//		if (i < 8)
//			printf(":");
//	}
//}

static void	print_ipv4(char	*data_storage)
{
	uint8_t	*data = (uint8_t *)data_storage;

	size_t	i = 0;
	while (i < 4)
	{
		std::cout << (int)(data[i]);
		i++;
		if (i < 4)
			std::cout << ".";
	}
}

static void	printSocket_in_local(struct sockaddr_in *addr, size_t tab_level)
{
	print_tab_level(tab_level);
	std::cout << "type: AF_INET;\n";
	print_tab_level(tab_level);
	std::cout << "port: " << htohl(addr->sin_port) << "\n";
	print_tab_level(tab_level);
	std::cout << "ip: ";
	print_ipv4(addr->sin_addr);
	std::cout << "\n";
}

static void printSocket_local(struct sockaddr_storage socket, size_t tab_level)
{
	if (socket.ss_family == AF_INET)
		printSocket_in_local((struct sockaddr_in)&sockaddr_storage, tab_level);
	if (socket.ss_family == AF_INET6)
		printSocket_in6_local((struct sockaddr_in6)&sockaddr_storage, tab_level);
}

void printSocket(struct sockaddr_storage socket)
{
	printSocket_local(socket, 0);
}

void	printClientMaxBodySize(size_t size)
{
	std::cout << "client_max_body_size: ";
	if (size < 1024)
	{
		std::cout << size << "B" << "\n";
		return ;
	}
	size = size / 1024;
	if (size < 1024)
	{
		std::cout << size << "KiB" << "\n";
		return ;
	}
	size = size / 1024;
	if (size < 1024)
	{
		std::cout << size << "MiB" << "\n";
		return ;
	}
	size = size / 1024;
	if (size < 1024)
	{
		std::cout << size << "GiB" << "\n";
		return ;
	}
	size = size / 1024;
	std::cout << size << "TiB" << "\n";
	return ;
}

void	printServerName(std::string name)
{
	std::cout << "server_name: " << name << ";\n";
}

void	printServer(t_server server)
{
	std::cout << "server\n";
	std::cout << "{\n";
	std::cout << "\t";
	printServerName(server.server_name);
	std::cout << "\t";
	printClientMaxBodySize(server.client_max_body_size);
	std::cout << "}\n";
}

//
//	this is how the mesage will be seen.
//
//	server
//	{
//		server_name: localhost taha.com;
//		client_max_body_size: 300MB;
//		sockets
//		{
//			socket1
//			{
//				type: AF_ITEN;
//				port: 12;
//				ip: 127.0.0.1;
//			}
//			socket2
//			{
//			...
//			}
//		...
//		}
//		error_pages
//		{
//			error_page1
//			{
//				path: /www/error/400.html;
//				status_code: 404;
//			}
//			error_page2
//			{
//			...
//			}
//		...
//		}
//		routes
//		{
//			route1
//			{
//				type: static;
//				status_code: 302;
//				body_text:	"http::/google.com";
//			}
//			route2
//			{
//				type: default;
//				accepted methods: GET, POST;
//				root:	/www/users;
//				directory_listing: yes;
//				index_file: 
//			}
//			route3
//			{
//			...
//			}
//		...
//		}
//	}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

