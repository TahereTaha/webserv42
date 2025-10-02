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

ServerResponse ServerManager::handleRequest(const Request& request) {
    Server* server = findServer(request);
    if (server) {
        return server->handleRequest(request);
    }
    
    // No server found, return 404
    return ServerResponse(404, "text/html", "<html><body><h1>404 Not Found</h1></body></html>");
}

Server* ServerManager::findServer(const Request& request) {
    // Try to match by Host header first
    const Headers& headers = request.getHeaders();
    
    // Check if Host header exists and get its value
    if (headers.has("Host")) {
        std::string hostHeader = headers.get("Host");
        
        // Try to match Host header with server names
        for (size_t i = 0; i < servers.size(); ++i) {
            const std::string& serverName = servers[i]->getServerName();
            if (serverName == hostHeader) {
                return servers[i];
            }
        }
    }
    
    // If no Host header match, return the first server (default server)
    if (!servers.empty()) {
        return servers[0];
    }
    
    return NULL;
}
