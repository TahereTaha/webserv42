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
	size_t	i = 0;
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

static void	printErrorPage_local(t_error_page error_page, size_t tab_level)
{
	print_tab_level(tab_level);
	std::cout << "path: " << error_page.uri << "\n";
	print_tab_level(tab_level);
	std::cout << "status_code: " << (int) error_page.status_code << "\n";
}

void	printErrorPage(t_error_page error_page)
{
	std::cout << "error_page\n";
	std::cout << "{\n";
	printErrorPage_local(error_page, 1);
	std::cout << "}\n";
	std::cout << std::endl;
}

static void	print_ipv6(char *data_storage)
{
	uint16_t *data = (uint16_t *)data_storage;

	size_t	i = 0;
	while (i < 8)
	{
		std::cout << (int)( ntohs(data[i]) );
		i++;
		if (i < 8)
			std::cout << ":" ;
	}
}

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

static void	printSocket_in6_local(struct sockaddr_in6 *addr, size_t tab_level)
{
	print_tab_level(tab_level);
	std::cout << "type: AF_INET6;\n";
	print_tab_level(tab_level);
	std::cout << "port: " << ntohl(addr->sin6_port) << "\n";
	print_tab_level(tab_level);
	std::cout << "ip: ";
	print_ipv6((char *)&addr->sin6_addr);
	std::cout << "\n";
}

static void	printSocket_in_local(struct sockaddr_in *addr, size_t tab_level)
{
	print_tab_level(tab_level);
	std::cout << "type: AF_INET;\n";
	print_tab_level(tab_level);
	std::cout << "port: " << ntohl(addr->sin_port) << "\n";
	print_tab_level(tab_level);
	std::cout << "ip: ";
	print_ipv4((char *)&addr->sin_addr);
	std::cout << "\n";
}

static void printSocket_local(struct sockaddr_storage socket, size_t tab_level)
{
	if (socket.ss_family == AF_INET)
		printSocket_in_local((struct sockaddr_in *)&socket, tab_level);
	if (socket.ss_family == AF_INET6)
		printSocket_in6_local((struct sockaddr_in6 *)&socket, tab_level);
}

void printSocket(struct sockaddr_storage socket)
{
	std::cout << "socket\n";
	std::cout << "{\n";
	printSocket_local(socket, 1);
	std::cout << "}\n";
	std::cout << std::endl;
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
	
	print_tab_level(1);
	printServerName(server.server_name);
	print_tab_level(1);
	printClientMaxBodySize(server.client_max_body_size);
	print_tab_level(1);
	std::cout << "sockets\n";
	print_tab_level(1);
	std::cout << "{\n";
	
	size_t i = 0;
	while (i < server.socket.size())
	{
		print_tab_level(2);
		std::cout << "socket number: " << (i + 1) << "\n";
		print_tab_level(2);
		std::cout << "{\n";
		printSocket_local(server.socket[i], 3);
		print_tab_level(2);
		std::cout << "}\n";
		i++;
	}
	
	print_tab_level(1);
	std::cout << "}\n";
	
	print_tab_level(1);
	std::cout << "error_pages\n";
	print_tab_level(1);
	std::cout << "{\n";
	
	i = 0;
	while (i < server.error_page.size())
	{
		print_tab_level(2);
		std::cout << "error_page number: " << (i + 1) << "\n";
		print_tab_level(2);
		std::cout << "{\n";
		printErrorPage_local(server.error_page[i], 3);
		print_tab_level(2);
		std::cout << "}\n";
		i++;
	}

	print_tab_level(1);
	std::cout << "}\n";

	std::cout << "}\n";
	std::cout << std::endl;
}

