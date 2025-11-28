#pragma once

#include <string>

class ServerResponse {
public:
	int         status_code;
	std::string content_type;
	std::string body;

	
	ServerResponse();
	
	ServerResponse(int code, const std::string &type, const std::string &b);
};
