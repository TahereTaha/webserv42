/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrMatchUtils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:22:11 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 12:34:36 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StrMatchUtils.hpp"

std::string strIter(std::string str, int (*func)(int))
{
	std::string result;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		result += func(*it);
	}
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

std::string getFirstOcurrence(const std::string& str, const std::string& toFind, bool caseSensitive = true)
{
	size_t pos;
	if (caseSensitive)
		pos = str.find(toFind);
	else
		pos = toUpper(str).find(toUpper(toFind));
	return pos == 0 ?  str.substr(pos, toFind.length()) : "";
}