/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:12:39 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 18:12:06 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./terminal/TestFactory/TerminalFactoryTest.hpp"

int main(void)
{
	TerminalFactoryTest factory("test 1234 abc 5678 defg90");
	factory.printTokens();
	return 0;
}