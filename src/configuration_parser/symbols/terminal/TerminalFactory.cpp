/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:22:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 16:01:57 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TerminalFactory.hpp"
#include "Terminal.hpp"
#include "./TestFactory/UndefinedSymbol.hpp"
#include "../Symbol.hpp"


TerminalFactory::TerminalFactory(void)
{}
// Dont know if this should be on the factory or the concrete class for this factory
int TerminalFactory::getTokenMatch(std::string content)
{	
	_constructors.setAll(content);
	if (_constructors.match == nullptr)
		_tokenVector.contents.push_back(new UndefinedSymbol());
	else
		_tokenVector.contents.push_back(_constructors.match->clone());
	return _tokenVector.contents.back()->length();
}

// Dont know if this should be on the factory or the concrete class for this factory
int TerminalFactory::getTokens(std::string content)
{
	size_t	i 	= 0;
	size_t	len = 0;

	while (i < content.length())
	{
		len = getTokenMatch(content.substr(i));
		len ? i += len : ++i; // ask taha what to do when no match is found
	}
	return i;
}

TerminalFactory::~TerminalFactory() {}


void TerminalFactory::printTokens()
{
	_tokenVector.print();
}