#pragma once

#include <vector>
#include "Server.hpp"
#include "ServerResponse.hpp"
#include "../src/http_request_parser/Request.hpp"

class ServerManager {
public:
    ServerManager();
    ~ServerManager();
    
    void addServer(const t_server& config);
    ServerResponse handleRequest(const Request& request);

private:
    std::vector<Server*> servers;
    
    Server* findServer(const Request& request);
};
