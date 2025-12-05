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

	Response		handleErrorRequest(const Request &request);
	Response       handleRequest(const Request &request);

	const std::vector<std::string>   &getServerName() const;
	t_server    _config;

private:
	
};
