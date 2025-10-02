#pragma once

#include <string>

struct ServerResponse {
    int status_code;
    std::string content_type;
    std::string body;
    
    ServerResponse() : status_code(200), content_type("text/html") {}
    ServerResponse(int code, const std::string& type, const std::string& content) 
        : status_code(code), content_type(type), body(content) {}
};
