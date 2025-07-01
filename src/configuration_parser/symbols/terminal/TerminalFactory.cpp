/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:22:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 19:28:16 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TerminalFactory.hpp"
#include "Terminal.hpp"
#include "./TestFactory/UndefinedSymbol.hpp"
#include "../Symbol.hpp"


TerminalFactory::TerminalFactory(void)
{
}

void TerminalFactory::SymbolReplaceLast(Terminal *symbol)
{
	if (_tokenVector.empty())
		return;
	delete _tokenVector.back();
	_tokenVector.push_back(symbol);
}

int TerminalFactory::AddNextSymbol(std::string content)
{
	Terminal	*result;
	size_t	 size = 0;

	_tokenVector.push_back(new UndefinedSymbol());
	for (Terminal* constructor : _constructors)
	{
		result = constructor->clone(content);
		size_t currentSize = result->getText().length();
		if (currentSize > size)
			SymbolReplaceLast(result);
		else
			delete result;
		currentSize > size ? size = currentSize : size;
	}
	return size;
}

int TerminalFactory::Lexer(std::string content)
{
	int added = 0;
	for(size_t i = 0; i < content.length(); i++)
	{
		std::string nextSymbol = content.substr(i);
		added = AddNextSymbol(nextSymbol);
		if (!added)
			// ask taha and not defined
		i += added - 1;
	}
	return added;
}
