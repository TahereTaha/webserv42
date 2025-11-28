 #pragma once

 #include <vector>
 #include "intermediate_representation.hpp"
 #include "Server.hpp"
 #include "ServerResponse.hpp"
 #include "Request.hpp"

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
