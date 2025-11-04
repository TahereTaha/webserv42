/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatahere <tatahere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:35:18 by tatahere          #+#    #+#             */
/*   Updated: 2025/11/04 17:47:50 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>

#include <ConfigurationParser.hpp>
#include <Args.hpp>
#include <textColors.h>
#include <parse_exception.hpp>
#include <multy_parse_exception.hpp>

#include <AParser.hpp>


//
//int	main(int argc, char **argv)
//{
//	try
//	{
//		Args				args(argc, argv);
//		ConfigurationParser	parser(args);
//
//		parser.readFile();
//		parser.scanning();
//		parser.parsing();
//		parser.analysis();
//		parser.transpiling();
//		std::cout << "starting web server." << std::endl;
//	}
//	catch (multy_parse_exception & e)
//	{
//		std::cerr << e.what() << std::flush;
//		return (1);
//	}
//	catch (const std::exception & e)
//	{
//		if (argc > 0)
//			std::cerr << RED << e.what() << RESET << std::endl;
//		else
//			std::cerr << e.what() << std::endl;
//		return (1);
//	}
//	return (0);
//}


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

int	main(void)
{
	//	testing the normalization without the pct encoding.
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
	//	testing the normalization with the pct encoding.
	{
		Path	path1("/taha%2f/tahere");

		path1.print();
	}
	return (0);
}

