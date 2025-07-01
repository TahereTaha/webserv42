/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:12:39 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 01:47:41 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./terminal/TestFactory/TerminalFactoryTest.hpp"

int main(void)
{
	TerminalFactoryTest factory("test 1234");
	// << Operator is overloaded in TerminalFactory.hpp frees the TerminalVector and create a memory leak
	// TerminalFactory *factoryPtr = &factory;
	// std::cout <<  *factoryPtr << std::endl;;
	return 0;
}