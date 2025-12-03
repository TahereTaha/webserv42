#include "ServerResponse.hpp"


ServerResponse::ServerResponse()
	: status_code(200),
	  content_type("text/html"),  // default content type rn, see if needs change maybe (?)
	  body(""),
	  location("")
{}


ServerResponse::ServerResponse(int code, const std::string &type, const std::string &b)
	: status_code(code),
	  content_type(type),
	  body(b),
	  location("")
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

    // Optional Location header for redirects
    if (!location.empty()) {
        resp += "Location: " + location + "\r\n";
    }

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
         // --- 2xx Success ---
        case 200: return "OK";
        case 201: return "Created";
        case 202: return "Accepted";
        case 204: return "No Content";

        // --- 3xx Redirection ---
        case 300: return "Multiple Choices";
        case 301: return "Moved Permanently";
        case 302: return "Found";                 // old name: "Moved Temporarily"
        case 303: return "See Other";
        case 304: return "Not Modified";
        case 305: return "Use Proxy";             // deprecated but valid
        case 307: return "Temporary Redirect";
        case 308: return "Permanent Redirect";

        // --- 4xx Client Errors ---
        case 400: return "Bad Request";
        case 401: return "Unauthorized";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 408: return "Request Timeout";
        case 411: return "Length Required";
        case 413: return "Payload Too Large";
        case 414: return "URI Too Long";
        case 415: return "Unsupported Media Type";

        // --- 5xx Server Errors ---
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 502: return "Bad Gateway";
        case 503: return "Service Unavailable";
        case 504: return "Gateway Timeout";

        default:  return "Unknown";
    }
}