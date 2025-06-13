/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatahere <tatahere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:53:34 by tatahere          #+#    #+#             */
/*   Updated: 2025/06/13 21:33:50 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/socket.h>

typedef	union u_ip
{
	struct in_addr	v4;
	struct in6_addr	v6;
}	t_ip;

typedef struct s_socket
{
	sa_family_t	family;
	t_ip		ip;
	in_port_t	port;
	int			default_server;		// this is only for the server
}	t_socket;

//	there are more status codes to be added.
typedef enum e_status_code
{
	RES_100 = 100,		//	continue
	RES_200 = 200,		//	ok
	RES_300 = 300,		//	multiple choice
	RES_400 = 400,		//	bad request
	RES_401 = 401,		//	unauthorized
	RES_402 = 402,		//	payment required
	RES_403 = 403,		//	forbidden
	RES_404 = 404,		//	not found
	RES_500 = 500,		//	internal server error
}	t_status_code;

typedef struct s_error_page
{
	t_status_code	error_code;
	std::string		pathname;
}	t_error_page;

//	routes still need some conceptualization.

//typedef enum e_http_method
//{
//	GET,
//	HEAD,
//	OPTIONS,
//	TRACE,
//	PUT,
//	DELETE,
//	POST,
//	PATCH,
//	CONNECT,
//}	t_http_method;
//
//typedef struct s_route
//{
//	std::bitset<9>	accepted_methods;
//	
//}	t_route;

typedef struct s_server
{
	std::string					server_name;
	std::vector<t_socket>		sockets;
	std::vector<t_error_page>	error_pages;
	size_t						client_max_body_size;
//	std::vector<t_route>		routes;
}	t_server;


