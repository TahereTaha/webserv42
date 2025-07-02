/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalFactoryTest.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:08:30 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 16:36:59 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TerminalFactoryTest.hpp"
#include "AlphaToken.hpp"
#include "NumberToken.hpp"
#include "AlphaNumericalToken.hpp"

TerminalFactoryTest::TerminalFactoryTest(std::string content)
{
	_constructors.contents.push_back(new AlphaToken());
	_constructors.contents.push_back(new NumberToken());
	_constructors.contents.push_back(new AlphaNumericalToken());
	TerminalFactory::getTokens(content);
}

TerminalFactoryTest::~TerminalFactoryTest() { }





