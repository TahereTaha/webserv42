
#include <iostream>
#include <fstream>
#include "intermediate_representation.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "Headers.hpp"
#include "ControlData.hpp"


static t_server makeTestServer() {
	t_server s;                                        
	s.server_name = "localhost";                     
	s.client_max_body_size = 1024 * 1024;             

	t_route r;
	r.uri = "/";                                     
	r.response_type = DEFAULT;                        
	t_default_response d;
	d.root = "./www";                               
	d.directory_listing_enabled = 0;                 
	d.index_file = "index.html";                     
	d.accepted_methods.push_back(GET);                
	d.accepted_methods.push_back(POST);               
	d.accepted_methods.push_back(DELETE);             
	r.default_response = d;                           
	s.route.push_back(r);                             

	t_route r2;
	r2.uri = "/static";                             
	r2.response_type = DEFAULT;                        
	t_default_response d2;
	d2.root = "./assets";                           
	d2.directory_listing_enabled = 0;                 
	d2.index_file = "";                             
	d2.accepted_methods.push_back(GET);               
	r2.default_response = d2;
	s.route.push_back(r2);                            

	return s;                                         
}

static void printSummary(const std::string &label, const Response &resp) {
	const ServerResponse &res = resp.sres;
	std::cout << "== " << label << " ==\n";
	std::cout << "Status: " << res.status_code
	          << ", Content-Type: " << res.content_type
	          << ", Body length: " << res.body.size() << "\n\n";
}

static Response runCase(Server &srv, const std::string &method,
		const std::string &target, const std::string &body) {
	ControlData cd(method, target, "HTTP/1.1");
	Headers     h;
	Request     req(cd, h, body);
	return srv.handleRequest(req);
}

int main() {
	system("mkdir -p www assets www/dir");
	{
		std::ofstream f("www/index.html");
		f << "<html><body><h1>Index</h1></body></html>";
	}
	{
		std::ofstream f("www/file.txt");
		f << "plain text file";
	}
	{
		std::ofstream f("www/todelete.txt");
		f << "to be deleted";
	}
	{
		std::ofstream f("www/dir/a.txt");
		f << "A";
	}
	{
		std::ofstream f("assets/style.css");
		f << "body { background: #fff; }";
	}

	t_server cfg = makeTestServer();
	Server    srv(cfg);

	printSummary("GET /index.html (existing)",
	             runCase(srv, "GET", "/index.html", ""));

	printSummary("GET /missing.html (should 404)",
	             runCase(srv, "GET", "/missing.html", ""));

	printSummary("POST /upload.txt (create)",
	             runCase(srv, "POST", "/upload.txt", "uploaded content"));

	printSummary("DELETE /todelete.txt (existing)",
	             runCase(srv, "DELETE", "/todelete.txt", ""));

	printSummary("DELETE /todelete.txt again (should 404)",
	             runCase(srv, "DELETE", "/todelete.txt", ""));

	printSummary("PUT /index.html (unsupported, should 405)",
	             runCase(srv, "PUT", "/index.html", ""));

	std::string bigBody(cfg.client_max_body_size + 1, 'x');
	printSummary("POST body too large (should 413)",
	             runCase(srv, "POST", "/big.txt", bigBody));

	return 0;
}

