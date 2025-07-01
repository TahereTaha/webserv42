/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:22:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 01:46:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TerminalFactory.hpp"
#include "Terminal.hpp"
#include "./TestFactory/UndefinedSymbol.hpp"
#include "../Symbol.hpp"


TerminalFactory::TerminalFactory(void)
{
}

int TerminalFactory::pushBack(std::string content)
{	
	_constructors.setAll(content);
	if (_constructors.match == nullptr)
		_tokenVector.push_back(new UndefinedSymbol());
	else
		_tokenVector.push_back(_constructors.match->clone());
	return _tokenVector.back()->length();
}


int TerminalFactory::Lexer(std::string content)
{
	size_t	i 	= 0;
	size_t	len = 0;

	while (i < content.length())
	{
		len = pushBack(content.substr(i));
		len ? i += len : ++i; // ask taha what to do when no match is found
	}
	return i;
}

TerminalFactory::~TerminalFactory() {}

std::ostream& operator<<(std::ostream& os, const TerminalFactory& tf) {
    TerminalVector content = tf.getContent();
    for (TerminalVector::iterator it = content.begin(); it != content.end(); it++) {
		std::string text = (*it)->getText();
            os << text << " ";
    }
    return os;
}