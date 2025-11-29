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

std::string ServerResponse::to_string() const {
    std::string resp;

    // ---- Status line ----
    resp += "HTTP/1.1 ";

    {
        std::stringstream ss;
        ss << status_code;
        resp += ss.str();
    }

    resp += " ";
    resp += get_status_message(status_code);
    resp += "\r\n";

    // ---- Headers ----
    resp += "Content-Type: " + content_type + "\r\n";

    {
        std::stringstream ss;
        ss << body.size();
        resp += "Content-Length: " + ss.str() + "\r\n";
    }

    resp += "Connection: close\r\n";

    // End of headers
    resp += "\r\n";

    // ---- Body ----
    resp += body;

    return resp;
}

std::string ServerResponse::get_status_message(int code) const {
    switch (code) {
        case 200: return "OK";
        case 400: return "Bad Request";
        case 404: return "Not Found";
        case 500: return "Internal Server Error";
        default:  return "Unknown";
    }
}