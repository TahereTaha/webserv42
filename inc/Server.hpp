#pragma once

#include <string>
#include "intermediate_representation.hpp"
#include "ServerResponse.hpp"
#include "Request.hpp"

class Server {
public:

	Server(const t_server &config);
	Server(const Server &other);
	Server &operator=(const Server &other);
	~Server();

	Response       handleRequest(const Request &request);

	const std::string   &getServerName() const;

private:
	
	t_server    _config;
};
