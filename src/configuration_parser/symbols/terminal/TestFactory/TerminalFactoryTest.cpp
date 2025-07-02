/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalFactoryTest.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:08:30 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 02:03:46 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TerminalFactoryTest.hpp"
#include "TestFactory.hpp"
#include "NumberToken.hpp"

TerminalFactoryTest::TerminalFactoryTest(std::string content)
	: TerminalFactory()
{
	_constructors.push_back(new TestFactory());
	_constructors.push_back(new NumberToken());
	TerminalFactory::getTokens(content);
}

TerminalFactoryTest::~TerminalFactoryTest() { }





