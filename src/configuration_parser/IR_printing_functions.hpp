#pragma once

#include <intermediate_representation.hpp>

#include <string>
#include <sys/socket.h>

std::string	getHTTPMethodSring(t_http_method method);
std::string	getResponseTypeSring(t_response_type type);




//void	printErrorPage(t_error_page error_page);
//void	printStaticResponse(t_static_response static_response);
//void	printRedirectResponse(t_redirect_response redirect_response);
//void	printDefaultResponse(t_default_response default_response);
//void	printRoute(t_route route);

void	printSocket(struct sockaddr_storage);

void	printClientMaxBodySize(size_t size);

void	printServerName(std::string	name);

void	printServer(t_server server);

