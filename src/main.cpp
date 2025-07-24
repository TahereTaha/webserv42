/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatahere <tatahere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:35:18 by tatahere          #+#    #+#             */
/*   Updated: 2025/07/23 18:29:28 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>

#include <Parser.hpp>
#include <Args.hpp>
#include <textColors.h>
#include <parse_exception.hpp>

int	main(int argc, char **argv)
{
	try
	{
		Args	args(argc, argv);
		Parser	parser(args);
		parser.readFile();
		parser.scanning();
		parser.syntaxAnalysis();
		parser.semanticAnalysis();
		parser.initializeServer();
		std::cout << "starting web server." << std::endl;
	}
	catch (parse_exception & e)
	{
//		e.makeErrorMsg();
		std::cerr << e.what() << std::endl;
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
