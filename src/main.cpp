
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatahere <tatahere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:35:18 by tatahere          #+#    #+#             */
/*   Updated: 2025/11/06 14:26:49 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>

#include <ConfigurationParser.hpp>
#include <Args.hpp>
#include <textColors.h>
#include <parse_exception.hpp>
#include <multy_parse_exception.hpp>
#include <intermediate_representation.hpp>

#include <AParser.hpp>

#include <map>

#include <EpollConnectionManager.hpp>
#include <Socket.hpp>
#include <iostream>
#include <Log.hpp>

#include <setUpSockets.hpp>

#include <ServerManager.hpp>

int	main(int argc, char **argv)
{
	try
	{
		Args				args(argc, argv);
		ConfigurationParser	parser(args);

		parser.readFile();
		parser.scanning();
		parser.parsing();
//		parser.analysis();
		return (0);
		std::vector<t_server>	servers = parser.getServers();

		ServerManager	server_manager;
		size_t	i = 0;
		while (i < servers.size())
		{
			server_manager.addServer(servers[i]);
			i++;
		}
        
		EventLog::init("event.log");
		std::map<int, Socket *>	listeningSockets = set_up_sockets(servers);

        EpollConnectionManager manager(listeningSockets, server_manager);
        EventLog::shutdown();

		std::cout << "starting web server." << std::endl;
	}
	catch (multy_parse_exception & e)
	{
		std::cerr << e.what() << std::flush;
		return (1);
	}
	catch (const std::exception & e)
	{
		if (argc > 0)
			std::cerr << RED << e.what() << RESET << std::endl;
		else
			std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}

//#include <URI.hpp>
//
//int main(void)
//{
//	try
//	{
//		URI	uri("/");
//		(void)uri;
//		std::cout << uri.getPath().getPathText() << std::endl;
//	}
//	catch (std::exception &e)
//	{
//		std::cout << e.what() << std::endl;
//	}
//	return (0);
//}
//

#include <URI.hpp>
#include <UserInfo.hpp>
#include <stdexcept>

//	full form and relative uris tests.

//int main(void)
//{
//	std::string	url = "http://taha:123@datatracker.ietf.org/doc/html/rfc3986#section-3";
////	std::string	url = "http://datatracker.ietf.org/doc/html/rfc3986#section-3";
////	std::string	url = "//datatracker.ietf.org/doc/html/rfc3986#section-3";
////	std::string	url = "/doc/html/rfc3986#section-3";
////	std::string	url = "doc/html/rfc3986#section-3";
//
//	URI	uri(url);
//	if(uri.getScheme() == scheme_HTTP)
//		std::cout << "it is http" << std::endl;
//	if(uri.getScheme() == scheme_HTTPS)
//		std::cout << "it is https" << std::endl;
//	try
//	{
//		std::cout << "the user is:" << uri.getAuthority().getUserInfo().getUser() << std::endl;
//	}
//	catch (std::exception &e)
//	{
//		std::cout << "there is no user set." << std::endl;
//		std::cout << e.what() << std::endl;
//	}
//	try
//	{
//		std::cout << "the password is:" << uri.getAuthority().getUserInfo().getPassword() << std::endl;
//	}
//	catch (std::exception &e)
//	{
//		std::cout << "there is no password set." << std::endl;
//		std::cout << e.what() << std::endl;
//	}
//}

//	ip literals uri tests.

//int main(void)
//{
//	try
//	{
//		URI	url1("http://126.1.0.42");
//		url1.getAuthority().getHost().getIp().print();
//		
//		URI	url2("http://126.1.77.42");
//		url2.getAuthority().getHost().getIp().print();
//		
//		URI	url3("http://[::]");
//		url3.getAuthority().getHost().getIp().print();
//
//		URI	url4("http://[23a::aab]");
//		url4.getAuthority().getHost().getIp().print();
//
//		URI	url5("http://[23a:3:ff:1234::]");
//		url5.getAuthority().getHost().getIp().print();
//
//		URI	url6("http://[23a:3:ff:1234::ca1]");
//		url6.getAuthority().getHost().getIp().print();
//	}
//	catch (std::exception &e)
//	{
//		std::cout << "this exception is: " << e.what() << std::endl;
//		return (1);
//	}
//}

#include <Path.hpp>

//
//int	main(void)
//{
//	//	testing the normalization without the pct encoding.
//	{
//		Path	path1("/taha/tahere");
//		Path	path2("/taha/tahere/");
//		Path	path3("taha/tahere");
//		Path	path4("../taha//tahere");
//		Path	path5("pedro/../taha/./tahere");
//	
//		path1.print();
//		path2.print();
//		path3.print();
//		path4.print();
//		path5.print();
//	}
//	//	testing the normalization with the pct encoding.
//	{
//		Path	path1("/taha%2f/tahere");
//
//		path1.print();
//	}
//	return (0);
//}

//int main(void)
//{
//	{
//		Path	path1("hola_mundo");
//		Path	path2("hola%5fmundo");
//		Path	path3("hola__mundo");
//
//		std::cout << "comparison with two ecual paths: " << (int)(path1 == path2) << std::endl;
//		std::cout << "comparison with two not ecual paths: " << (int)(path2 == path3) << std::endl;
//	}
//	{
//		Path	path1("/taha/tahere/el%20berkani");
//		Path	path2("/taha/tahere/");
//		Path	path3("/mohamed/tahere/");
//		Path	path4("/taha/tahere/el%20berkani/sthhoeunta/stnaoehusn/tohenut/tuh/ooeu/oeu/oeu");
//
//		std::cout << "is path prefix of: " << path2.is_prefix_of(path1) << std::endl;
//		std::cout << "is path prefix of: " << path2.is_prefix_of(path2) << std::endl;
//		std::cout << "is path prefix of: " << path2.is_prefix_of(path3) << std::endl;
//		std::cout << "is path prefix of: " << path2.is_prefix_of(path4) << std::endl;
//	}
//	return (0);
//}
//

//
//int	main(void)
//{
//	URI	uri("https://datatracker.ietf.org/doc/html/rfc3986?user=taha#section-3");
//	std::cout << uri.getQuery().getText() << std::endl;
//	std::cout << uri.getFragment().getText() << std::endl;
//	return (0);
//}
//
//
//#include <sys/socket.h>
//#include <IpLiteral.hpp>
//#include <arpa/inet.h>
//#include <string.h>
//
//#define MY_IP "ff1:2:ad3::cd6:7:aaa8"
//
//int	main(void)
//{
//	try	
//	{
//	uint8_t	my_ipv4[IP_V6_DATA_SIZE];
//	uint8_t	std_ipv4[IP_V6_DATA_SIZE];
//
//	IpLiteral	ip(std::string("[") + MY_IP + "]");
//	uint8_t		*data = ip.getData();
//	memcpy(my_ipv4, data,sizeof(my_ipv4));
//	inet_pton(AF_INET6, MY_IP, std_ipv4);
//
//	size_t	i = 0;
//	while (i < IP_V6_DATA_SIZE)
//	{
//		std::cout << "mine at pos " << i << ": " << (int)my_ipv4[i] << std::endl;
//		std::cout << "std at pos " << i << ": " << (int)std_ipv4[i] << std::endl;
//		i++;
//	}
//	
//	}
//	catch (std::exception & e)
//	{
//		std::cout << e.what()  << std::endl;
//	}
//	return (0);
//}
//
