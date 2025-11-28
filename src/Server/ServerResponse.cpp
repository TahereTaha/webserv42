#include "ServerResponse.hpp"


ServerResponse::ServerResponse()
	: status_code(200),
	  content_type("text/html"),  // default content type rn, see if needs change maybe (?)
	  body("")
{}


ServerResponse::ServerResponse(int code, const std::string &type, const std::string &b)
	: status_code(code),
	  content_type(type),
	  body(b)
{}
