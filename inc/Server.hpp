#pragma once

#include <string>
#include <vector>
#include <map>
#include "ServerResponse.hpp"
#include "intermediate_representation.hpp"
#include "../src/http_request_parser/Request.hpp"

class Server {
public:
    Server(const t_server& config);
    ~Server();
    
    ServerResponse handleRequest(const Request& request);
    const std::string& getServerName() const;

private:
    t_server config;
    
    // Core file serving
    ServerResponse serveFile(const std::string& path);
    std::string getContentType(const std::string& filename);
    bool fileExists(const std::string& path);
    bool isDirectory(const std::string& path);
    
    // HTTP method validation
    bool isMethodAllowed(const std::string& method, const t_route& route);
    
    // Directory operations
    ServerResponse generateDirectoryListing(const std::string& path);
    
    // Error handling
    ServerResponse getErrorPage(int status_code);
    ServerResponse getDefaultErrorPage(int status_code);
    
    // File upload handling
    ServerResponse handleFileUpload(const Request& request, const t_route& route);
    bool saveUploadedFile(const std::string& content, const std::string& filename, const std::string& upload_dir);
    
    // HTTP redirection
    ServerResponse handleRedirection(const t_route& route);
    
    // Request validation
    bool isRequestBodySizeValid(const Request& request);
    
    // Utility methods
    std::string extractFilenameFromPath(const std::string& path);
    std::string joinPath(const std::string& base, const std::string& path);
};
