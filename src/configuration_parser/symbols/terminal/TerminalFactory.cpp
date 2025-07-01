/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:22:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 18:16:15 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TerminalFactory.hpp"
#include "Terminal.hpp"
#include "NotDefinedSymbol.hpp"
#include "Symbol.hpp"


int TerminalFactory::AddNextSymbol(std::string content)
{
	Terminal	*result;
	size_t	 size = 0;

	_tokenVector.push_back(new NotDefinedSymbol());
	for (Terminal* constructor : _constructors)
	{
		result = constructor->clone(content);
		size_t currentSize = result->getText().length();
		if (currentSize > size)
		{
		 size = result->getText().length();
			delete _tokenVector.back();
			_tokenVector.back() = result;
		}
		else
			delete result;
	}
	return size;
}

TerminalFactory::TerminalFactory(std::string content)
{
	int added = 0;
	for(int i = 0; i < content.length(); i++)
	{
		std::string nextSymbol = content.substr(i);
		added = AddNextSymbol(nextSymbol);
		if (!added)
			// ask taha and not defined
		i += added - 1;
	}
	
}
