#include "../inc/ServerManager.hpp"

ServerManager::ServerManager() {
}

ServerManager::~ServerManager() {
    for (size_t i = 0; i < servers.size(); ++i) {
        delete servers[i];
    }
    servers.clear();
}

void ServerManager::addServer(const t_server& config) {
	servers.push_back(new Server(config));
}

Response ServerManager::handleErrorRequest(const Request& request)
{
	Server* server = findServer(request);
	if (server) {
		return server->handleErrorRequest(request);
	}
	Response r;
	r.status = RESP_ERR;
	r.sres = ServerResponse(request.getErrorCode(), "text/html", std::string("<html><body><h1>") + get_status_message(request.getErrorCode())  + "</h1></body></html>");
	r.pathToCgi = "";
	return (r);
}

Response ServerManager::handleRequest(const Request& request) {
	Server* server = findServer(request);
	if (server) {
		return server->handleRequest(request);
	}
	Response r;
	r.status = RESP_ERR;
	r.sres = ServerResponse(404, "text/html", "<html><body><h1>404 Not Found</h1></body></html>");
	r.pathToCgi = "";
	return r;
}

#include <intermediate_representation.hpp>
#include <Authority.hpp>
#include <iostream>

static int	is_server_listeng_on_port(t_server server, Authority ip_port)
{
	size_t i = 0;
	while (i < server.socket.size())
	{
		if (ip_port.getPort() == ((struct sockaddr_in *) &server.socket[i])->sin_port)
			return (1);
		i++;
	}
	return (0);
}

Server* ServerManager::findServer(const Request& request) {
    
    const Headers& headers = request.getHeaders();
    
    // Check if Host header exists and get its value
    if (headers.has("Host")) {
        std::string hostHeader = headers.get("Host");
        
       
        for (size_t i = 0; i < servers.size(); ++i) {
            const std::string& serverName = servers[i]->getServerName();
            if (serverName == hostHeader) {
                return servers[i];
            }
			Authority ip_port(hostHeader);
			if (is_server_listeng_on_port(servers[i]->_config, ip_port))
			{
				return (servers[i]);
			}
        }
    }

    if (!servers.empty()) {
        return servers[0];
    }
    
    return NULL;
}
