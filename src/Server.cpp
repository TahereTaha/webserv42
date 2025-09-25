#include "../inc/Server.hpp"
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <algorithm>

Server::Server(const t_server& config) : config(config) {
}

Server::~Server() {
}

ServerResponse Server::handleRequest(const Request& request) {
    const std::string& uri = request.getControlData().uri.getPathString();
    const std::string& method = request.getControlData().method;
    
    // Validate request body size
    if (!isRequestBodySizeValid(request)) {
        return getErrorPage(413); // Payload Too Large
    }
    
    // Find matching route
    for (size_t i = 0; i < config.route.size(); ++i) {
        const t_route& route = config.route[i];
        if (uri.find(route.uri) == 0) {  // Simple prefix matching
            
            // Check if method is allowed for this route
            if (!isMethodAllowed(method, route)) {
                return getErrorPage(405); // Method Not Allowed
            }
            
            // Handle different response types
            if (route.response_type == STATIC) {
                return ServerResponse(route.static_response.status_code, 
                                    "text/html", 
                                    route.static_response.text);
            }
            else if (route.response_type == REDIRECT) {
                return handleRedirection(route);
            }
            else if (route.response_type == DEFAULT) {
                std::string file_path = joinPath(route.default_response.root, uri.substr(route.uri.length()));
                
                // Handle POST requests (file uploads)
                if (method == "POST" && route.default_response.upload_enabled) {
                    return handleFileUpload(request, route);
                }
                
                // Handle DELETE requests
                if (method == "DELETE") {
                    if (fileExists(file_path)) {
                        if (unlink(file_path.c_str()) == 0) {
                            return ServerResponse(200, "text/html", "<html><body><h1>File deleted successfully</h1></body></html>");
                        } else {
                            return getErrorPage(500);
                        }
                    } else {
                        return getErrorPage(404);
                    }
                }
                
                // Default file for directory requests
                if (uri == route.uri && !route.default_response.index_file.empty()) {
                    file_path = joinPath(route.default_response.root, route.default_response.index_file);
                }
                
                // Check if it's a directory
                if (isDirectory(file_path)) {
                    if (route.default_response.directory_listing_enabled) {
                        return generateDirectoryListing(file_path);
                    } else {
                        return getErrorPage(403); // Forbidden
                    }
                }
                
                // Serve regular file
                return serveFile(file_path);
            }
        }
    }
    
    // No route found
    return getErrorPage(404);
}

const std::string& Server::getServerName() const {
    return config.server_name;
}

ServerResponse Server::serveFile(const std::string& path) {
    if (!fileExists(path)) {
        return ServerResponse(404, "text/html", "<html><body><h1>404 Not Found</h1></body></html>");
    }
    
    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        return ServerResponse(500, "text/html", "<html><body><h1>500 Internal Server Error</h1></body></html>");
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return ServerResponse(200, getContentType(path), buffer.str());
}

std::string Server::getContentType(const std::string& filename) {
    size_t dot_pos = filename.find_last_of('.');
    if (dot_pos == std::string::npos) {
        return "text/plain";
    }
    
    std::string extension = filename.substr(dot_pos + 1);
    if (extension == "html" || extension == "htm") {
        return "text/html";
    } else if (extension == "css") {
        return "text/css";
    } else if (extension == "js") {
        return "application/javascript";
    } else if (extension == "jpg" || extension == "jpeg") {
        return "image/jpeg";
    } else if (extension == "png") {
        return "image/png";
    } else if (extension == "gif") {
        return "image/gif";
    }
    
    return "text/plain";
}

bool Server::fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

// New functions to support webserver requirements
bool Server::isRequestBodySizeValid(const Request& request) {
    const std::string& body = request.getBody();
    return body.length() <= config.client_max_body_size;
}

bool Server::isMethodAllowed(const std::string& method, const t_route& route) {
    if (route.response_type != DEFAULT) {
        return true; // STATIC and REDIRECT routes allow all methods
    }
    
    const std::vector<t_http_method>& allowed = route.default_response.accepted_methods;
    
    t_http_method request_method;
    if (method == "GET") request_method = GET;
    else if (method == "POST") request_method = POST;
    else if (method == "DELETE") request_method = DELETE;
    else return false; // Unknown method
    
    return std::find(allowed.begin(), allowed.end(), request_method) != allowed.end();
}

ServerResponse Server::handleRedirection(const t_route& route) {
    std::string location = route.redirect_response.location;
    std::string body = "<html><body><h1>Redirecting to " + location + "</h1></body></html>";
    
    ServerResponse response(route.redirect_response.status_code, "text/html", body);
    // Note: In a full implementation, you'd add Location header here
    return response;
}

ServerResponse Server::handleFileUpload(const Request& request, const t_route& route) {
    const std::string& body = request.getBody();
    const std::string& upload_dir = route.default_response.upload_dir;
    
    if (upload_dir.empty()) {
        return getErrorPage(403); // Uploads not configured
    }
    
    // Simple file upload implementation
    // In a real implementation, you'd parse multipart/form-data
    std::string filename = "uploaded_file.txt"; // This should be extracted from the request
    std::string full_path = joinPath(upload_dir, filename);
    
    if (saveUploadedFile(body, full_path, upload_dir)) {
        return ServerResponse(200, "text/html", "<html><body><h1>File uploaded successfully</h1></body></html>");
    } else {
        return getErrorPage(500);
    }
}

bool Server::saveUploadedFile(const std::string& content, const std::string& filename, const std::string& upload_dir) {
    // Create upload directory if it doesn't exist
    struct stat st;
    if (stat(upload_dir.c_str(), &st) != 0) {
        // Directory doesn't exist, try to create it
        if (mkdir(upload_dir.c_str(), 0755) != 0) {
            return false;
        }
    }
    
    std::ofstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    file.write(content.c_str(), content.length());
    file.close();
    
    return true;
}

ServerResponse Server::generateDirectoryListing(const std::string& path) {
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        return getErrorPage(500);
    }
    
    std::stringstream html;
    html << "<html><head><title>Directory listing for " << path << "</title></head>";
    html << "<body><h1>Directory listing for " << path << "</h1>";
    html << "<ul>";
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string name = entry->d_name;
        if (name == ".") continue; // Skip current directory
        
        html << "<li><a href=\"" << name;
        if (entry->d_type == DT_DIR) {
            html << "/";
        }
        html << "\">" << name;
        if (entry->d_type == DT_DIR) {
            html << "/";
        }
        html << "</a></li>";
    }
    
    html << "</ul></body></html>";
    closedir(dir);
    
    return ServerResponse(200, "text/html", html.str());
}

bool Server::isDirectory(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

std::string Server::joinPath(const std::string& base, const std::string& path) {
    if (base.empty()) return path;
    if (path.empty()) return base;
    
    std::string result = base;
    if (result[result.length() - 1] != '/') {
        result += "/";
    }
    
    // Remove leading slash from path if present
    std::string clean_path = path;
    if (!clean_path.empty() && clean_path[0] == '/') {
        clean_path = clean_path.substr(1);
    }
    
    return result + clean_path;
}

std::string Server::extractFilenameFromPath(const std::string& path) {
    size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(pos + 1);
}

ServerResponse Server::getErrorPage(int status_code) {
    // Try to find configured error page
    for (size_t i = 0; i < config.error_page.size(); ++i) {
        if (config.error_page[i].status_code == static_cast<t_status_code>(status_code)) {
            return serveFile(config.error_page[i].uri);
        }
    }
    
    // Return default error page
    return getDefaultErrorPage(status_code);
}

ServerResponse Server::getDefaultErrorPage(int status_code) {
    std::string title, message;
    
    switch (status_code) {
        case 400: title = "Bad Request"; message = "The request could not be understood."; break;
        case 403: title = "Forbidden"; message = "Access to this resource is forbidden."; break;
        case 404: title = "Not Found"; message = "The requested resource was not found."; break;
        case 405: title = "Method Not Allowed"; message = "The request method is not allowed."; break;
        case 413: title = "Payload Too Large"; message = "The request body is too large."; break;
        case 500: title = "Internal Server Error"; message = "An internal server error occurred."; break;
        default: title = "Error"; message = "An error occurred."; break;
    }
    
    std::stringstream ss;
    ss << status_code;
    std::string status_str = ss.str();
    
    std::string body = "<html><head><title>" + title + "</title></head>"
                      "<body><h1>" + status_str + " " + title + "</h1><p>" + message + "</p></body></html>";
    
    return ServerResponse(status_code, "text/html", body);
}
