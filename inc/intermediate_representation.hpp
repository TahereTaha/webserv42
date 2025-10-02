#pragma once

#include <vector>
#include <string>

#include <sys/socket.h>

typedef	unsigned int t_status_code;

typedef enum
{
	GET,
	POST,
	DELETE,
}	t_http_method;

typedef struct
{
	t_status_code	status_code;
	std::string		uri;
}	t_error_page;

typedef enum
{
	DEFAULT,
	STATIC,
	REDIRECT,
}	t_response_type;

typedef struct
{
	t_status_code	status_code;
	std::string		text;	//	this can be a uri or just the body of the response.
}	t_static_response;

typedef struct
{
	t_status_code	status_code;
	std::string		location;
}	t_redirect_response;

typedef struct
{
	std::vector<t_http_method>	accepted_methods;
	std::string					root;
	int							directory_listing_enabled;
	std::string					index_file;
	std::string					upload_dir;				// Directory for file uploads
	int							upload_enabled;			// Whether uploads are allowed
}	t_default_response;

typedef struct
{
	//	for matching the request with the location.
	std::string					uri;

	//	how the location will answere to a request.
	t_response_type				response_type;
	t_static_response			static_response;
	t_default_response			default_response;
	t_redirect_response			redirect_response;
}	t_route;

typedef struct
{
	std::vector<sockaddr_storage>	socket;
	std::string						server_name;
	std::vector<t_error_page>		error_page;
	size_t							client_max_body_size;
	std::vector<t_route>			route;
}	t_server;
