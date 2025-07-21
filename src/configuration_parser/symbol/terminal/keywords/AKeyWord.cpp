/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AKeyWord.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:22:10 by capapes           #+#    #+#             */
/*   Updated: 2025/07/21 13:12:00 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AKeyWord.hpp"

std::string strIter(std::string str, int (*func)(int))
{
	std::string result;
	
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
		result += func(*it);
	return result;
}

std::string toUpper(std::string str)
{
	return strIter(str, std::toupper);
}

std::string toLower(std::string str)
{
	return strIter(str, std::tolower);
}

bool startsWith(const std::string& str, const std::string& toFind, bool caseSensitive)
{
	size_t pos;
	if (caseSensitive)
		pos = str.rfind(toFind, toFind.length());
	else
		pos = toUpper(str).find(toUpper(toFind));
	return pos == 0;
}



AKeyWord::AKeyWord(void)
{
	this->_text = "";
}

AKeyWord::AKeyWord(const std::string & str) : ATerminal(),  _keyWord(str)
{
	this->_text = "";
}

size_t		AKeyWord::getTerminalSizeOnStr(const std::string & str) const
{
	return startsWith(str, _keyWord) ? _keyWord.length() : 0;
}

