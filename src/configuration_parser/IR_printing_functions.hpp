#pragma once

#include <intermediate_representation.hpp>

#include <string>
#include <sys/socket.h>

std::string	getHTTPMethodSring(t_http_method method);
std::string	getResponseTypeSring(t_response_type type);

void	printRoute(t_route route);

void	printErrorPage(t_error_page error_page);

void	printSocket(struct sockaddr_storage);

void	printClientMaxBodySize(size_t size);

void	printServerName(std::string	name);

void	printServer(t_server server);



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

