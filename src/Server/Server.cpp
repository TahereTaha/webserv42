#include "Server.hpp"          
#include <sys/stat.h>           
#include <dirent.h>            
#include <fcntl.h>              
#include <unistd.h>             
#include <errno.h>              
#include <fstream>              
#include <sstream>              


Server::Server(const t_server &config)
	: _config(config) {}


Server::Server(const Server &other)
	: _config(other._config) {}


Server &Server::operator=(const Server &other) {
	if (this != &other)
		_config = other._config;    
	return *this;                
}


Server::~Server() {}


const std::string &Server::getServerName() const {
	return _config.server_name;
}

// =====================================================================
//                         INTERNAL HELPERS
// =====================================================================

// convert an HTTP method string into the corresponding
// t_http_method enum value in the intermediate representation
static t_http_method methodFromString(const std::string &m) {
	if (m == "GET")
		return GET;       
	if (m == "POST")
		return POST;      
	if (m == "DELETE")
		return DELETE;   
	return GET;          
}

// check whether the given route allows the specified method...
// is this implemented method allowed on this specific route according to config?
static bool methodAllowed(const t_route &route, const std::string &method) {
	t_http_method m = methodFromString(method);  // Convert string to enum.
	for (std::vector<t_http_method>::const_iterator it = route.default_response.accepted_methods.begin();
		 it != route.default_response.accepted_methods.end(); ++it) {
		if (*it == m)
			return true;   // found a matching allowed method.
	}
	return false;        // method not in the allowed list
}

// find the best matching route for the given request path. It iterates over
// all routes and chooses the one whose URI is the longest prefix of path
static const t_route *findBestRoute(const t_server &cfg, const std::string &path) {
	const t_route *best = NULL;  // pointer to the best route found so far
	std::string    bestUri;      // store the URI string of the best route

	for (std::vector<t_route>::const_iterator it = cfg.route.begin(); it != cfg.route.end(); ++it) {
		const std::string &loc = it->uri;   // location prefix / or /static
		if (loc.empty())
			continue;                      // skip empty route URIs
		if (path.compare(0, loc.size(), loc) == 0) {
			
			if (best == NULL || loc.size() > bestUri.size()) {
				best = &(*it);              
				bestUri = loc;              
			}
		}
	}
	return best;                          // may be NULL if no route matched
}


static bool isSupportedMethod(const std::string &method) {
	return (method == "GET" || method == "POST" || method == "DELETE");
}

// check whether a POST request exceeds the client_max_body_size

static bool isPostTooLarge(const t_server &cfg, const Request &request) {
	const ControlData  &cd   = request.getControlData();
	const std::string  &meth = cd.method;
	if (meth != "POST")
		return false;                            //only checks POST
	const std::string &body = request.getBody();
	if (cfg.client_max_body_size > 0 &&
	    body.size() > cfg.client_max_body_size)
		return true;
	return false;
}

// this is used to set
// an appropriate content type header when serving static files
// probably not strictly necessary, we can discuss if keep it or not
static std::string detectMimeType(const std::string &path) {
	std::string::size_type dot = path.rfind('.'); 
	if (dot == std::string::npos)
		return "text/plain";                  // no extension: default text
	std::string ext = path.substr(dot + 1);    
	if (ext == "html" || ext == "htm")
		return "text/html";
	if (ext == "css")
		return "text/css";
	if (ext == "js")
		return "application/javascript";
	if (ext == "png")
		return "image/png";
	if (ext == "jpg" || ext == "jpeg")
		return "image/jpeg";
	if (ext == "gif")
		return "image/gif";
	if (ext == "ico")
		return "image/x-icon";
	return "application/octet-stream";       // unknown extensions.
}

// Read the entire contents of a file into string
// used when serving files (GET, error pages): 
// it gives you “file -> string (body)” and tells you if the read worked
static bool readFileToString(const std::string &path, std::string &out) {
	std::ifstream file(path.c_str(), std::ios::in | std::ios::binary); // open file
	if (!file)
		return false;                        // opening failed
	std::ostringstream ss;                 // string stream
	ss << file.rdbuf();                    // read entire file buffer into stream
	out = ss.str();                        // Copy resulting string to 'out'.
	return true;                         
}

// Return true if is a directory
static bool isDirectory(const std::string &path) {
	struct stat st;                        
	if (stat(path.c_str(), &st) == -1)
		return false;                        // stat failed: non-directory.
	return S_ISDIR(st.st_mode);            
}

// look for a configured error page matching the given status code
static const t_error_page *findErrorPage(const t_server &cfg, int code) {
	for (std::vector<t_error_page>::const_iterator it = cfg.error_page.begin();
		 it != cfg.error_page.end(); ++it) {
		if ((int)it->status_code == code)
			return &(*it);                  // found a matching error page 
	}
	return NULL;                           // none found
}

// build a ServerResponse representing an error if a custom error page is
// configured it is used as the body if not a
// simple HTML message is generated
static ServerResponse buildErrorResponse(const t_server &cfg, int code, const std::string &fallbackMsg) {
	const t_error_page *ep = findErrorPage(cfg, code); // look for custom page.
	std::string body;
	if (ep && readFileToString(ep->uri, body))
		return ServerResponse(code, "text/html", body); 
	// HTML error body with the provided fallback message
	return ServerResponse(code, "text/html",
	                      std::string("<html><body><h1>") + fallbackMsg + "</h1></body></html>");
}


static std::string joinPath(const std::string &root, const std::string &suffix) {
	if (root.empty())
		return suffix;                       //no root: just return the suffix
	if (!root.empty() && root[root.size() - 1] == '/') {
		// root already ends with / avoid putting a double /
		if (!suffix.empty() && suffix[0] == '/')
			return root + suffix.substr(1); // skip leading / in suffix
		return root + suffix;              
	}
	if (!suffix.empty() && suffix[0] == '/')
		return root + suffix;              // root has no / but suffix already does
	return root + "/" + suffix;         //put a separator between them
}

// simple autoindex HTML generation for a directory
static bool generateAutoIndex(const std::string &path, const std::string &uri,
	                           std::string &out) {
	DIR *dir = opendir(path.c_str());      // open directory for reading entries
	if (!dir)
		return false;                        // could not open directory
	std::ostringstream html;
	html << "<html><body><h1>Index of " << uri << "</h1><ul>";
	struct dirent *ent;
	while ((ent = readdir(dir)) != NULL) {
		const char *name = ent->d_name;    // entry name (file or directory)
		// i'm skipping "." and ".." to avoid self and parent references
		if (name[0] == '.' && (name[1] == '\0' || (name[1] == '.' && name[2] == '\0')))
			continue;
		// add a list item with a simple hyperlink to the entry
		html << "<li><a href=\"" << name << "\">" << name << "</a></li>";
	}
	closedir(dir);                         
	html << "</ul></body></html>";       
	out = html.str();                      
	return true;                           
}

// build the response for a STATIC route
static ServerResponse handleStaticRoute(const t_route &route) {
	ServerResponse res;
	res.status_code = (int)route.static_response.status_code;
	res.content_type = "text/html";
	const std::string &loc = route.static_response.text;
	std::string body = "<html><body><h1>Redirect</h1>";
	if (!loc.empty())
		body += "<a href=\"" + loc + "\">" + loc + "</a>";
	body += "</body></html>";
	res.body = body;
	// If this is a 3xx status code and a target URL is configured,
	// populate the Location header so that browsers actually follow the redirect.
	if (res.status_code >= 300 && res.status_code < 400 && !loc.empty()) {
		res.location = loc;
	}
	return res;
}

// build the response for a DEFAULT route: map URI, handle directories,dispatch
// to method logic for files
static ServerResponse handleDefaultRoute(const t_server &cfg,
	const t_route &route,
	const std::string &method,
	const std::string &target,
	const Request &request) {
	
	std::string rel = target;       
	if (route.uri != "/" && rel.compare(0, route.uri.size(), route.uri) == 0)
		rel = rel.substr(route.uri.size()); 
	if (rel.empty())
		rel = "/";                     

	std::string fullPath = joinPath(route.default_response.root, rel);

	// if the result is a directory handle index or autoindex
	if (isDirectory(fullPath)) {
		if (!route.default_response.index_file.empty()) {
			// if an index file is configured append it and serve that
			fullPath = joinPath(fullPath, route.default_response.index_file);
		} else {
			// no index: either generate autoindex or return 403
			ServerResponse res;
			if (route.default_response.directory_listing_enabled) {
				std::string body;
				if (generateAutoIndex(fullPath, target, body)) {
					res.status_code = 200;
					res.content_type = "text/html";
					res.body = body;
				} else {
					res = buildErrorResponse(cfg, 500, "500 Internal Server Error");
				}
			} else {
				res = buildErrorResponse(cfg, 403, "403 Forbidden");
			}
			return res;               
		}
	}

	// handle method behavior for nondirectory targets
	if (method == "GET") {
		std::string body;
		if (!readFileToString(fullPath, body)) {
			// file missing or unreadable: 404.
			return buildErrorResponse(cfg, 404, "404 Not Found");
		}
		ServerResponse res;
		res.status_code = 200;              // OK
		res.content_type = detectMimeType(fullPath);
		res.body = body;                    // file contents
		return res;
	} else if (method == "POST") {
		// simple upload: overwrite target file with body
		const std::string &reqBody = request.getBody();
		std::ofstream out(fullPath.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
		if (!out)
			return buildErrorResponse(cfg, 500, "500 Internal Server Error");
		out.write(reqBody.c_str(), reqBody.size());
		if (!out)
			return buildErrorResponse(cfg, 500, "500 Internal Server Error");
		ServerResponse res;
		res.status_code = 201;          // created
		res.content_type = "text/plain";
		res.body = "Created";          // simple confirmation body
		return res;
	} else if (method == "DELETE") {
		
		if (unlink(fullPath.c_str()) == -1) {
			if (errno == ENOENT)
				return buildErrorResponse(cfg, 404, "404 Not Found");
			return buildErrorResponse(cfg, 500, "500 Internal Server Error");
		}
		ServerResponse res;
		res.status_code = 200;              // deletion successful
		res.content_type = "text/plain";
		res.body = "Deleted";             
		return res;
	}

	// should not be reached because unsupported methods are handled earlier
	return buildErrorResponse(cfg, 405, "405 Method Not Allowed");
}

// =====================================================================
//                      MAIN REQUEST HANDLER
// =====================================================================

#include <iostream>

Response Server::handleRequest(const Request &request) {
	const ControlData  &cd      = request.getControlData(); 
	const std::string  &method  = cd.method;                
	const std::string  &target  = cd.requestTarget;       

//	std::cout << "this is a server log:" << std::endl;
//	std::cout << cd.requestTarget << std::endl;
	// 1) validate method
	if (!isSupportedMethod(method)) {
		Response r;
		r.status = RESP_ERR;
		r.sres = buildErrorResponse(_config, 405, "405 Method Not Allowed");
		r.pathToCgi = "";
		return r;
	}

	// 2) check body size
	if (isPostTooLarge(_config, request)) {
		Response r;
		r.status = RESP_ERR;
		r.sres = buildErrorResponse(_config, 413, "413 Payload Too Large");
		r.pathToCgi = "";
		return r;
	}

	// 3) find best route
	const t_route *route = findBestRoute(_config, target);
	if (!route) {
		Response r;
		r.status = RESP_ERR;
		r.sres = buildErrorResponse(_config, 404, "404 Not Found");
		r.pathToCgi = "";
		return r;
	}

	// 4) check method allowance for DEFAULT routes
	if (route->response_type == DEFAULT && !methodAllowed(*route, method)) {
		Response r;
		r.status = RESP_ERR;
		r.sres = buildErrorResponse(_config, 405, "405 Method Not Allowed");
		r.pathToCgi = "";
		return r;
	}

	// 5) dispatch to STATIC or DEFAULT handling
	Response r;
	r.pathToCgi = "";
	if (route->response_type == STATIC) {
		r.status = RESP_OK;
		r.sres = handleStaticRoute(*route);
	} else {
		r.status = RESP_OK;
		r.sres = handleDefaultRoute(_config, *route, method, target, request);
	}
	return r;
}
