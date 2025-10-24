/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatahere <tatahere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:35:18 by tatahere          #+#    #+#             */
/*   Updated: 2025/10/24 12:34:37 by tatahere         ###   ########.fr       */
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

int main(void)
{
	std::string	url = "http://taha:123@datatracker.ietf.org/doc/html/rfc3986#section-3";
//	std::string	url = "http://datatracker.ietf.org/doc/html/rfc3986#section-3";
//	std::string	url = "//datatracker.ietf.org/doc/html/rfc3986#section-3";
//	std::string	url = "/doc/html/rfc3986#section-3";
//	std::string	url = "doc/html/rfc3986#section-3";

	URI	uri(url);
	if(uri.getScheme() == scheme_HTTP)
		std::cout << "it is http" << std::endl;
	if(uri.getScheme() == scheme_HTTPS)
		std::cout << "it is https" << std::endl;
	try
	{
		std::cout << "the user is:" << uri.getAuthority().getUserInfo().getUser() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "there is no user set." << std::endl;
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "the password is:" << uri.getAuthority().getUserInfo().getPassword() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "there is no password set." << std::endl;
		std::cout << e.what() << std::endl;
	}
}

