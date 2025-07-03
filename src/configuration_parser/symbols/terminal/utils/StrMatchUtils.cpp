/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrMatchUtils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:22:11 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 15:10:08 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StrMatchUtils.hpp"

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

int main()
{
	// Test the utility functions
	std::string testStr = "HelloWorld";
	std::string upperStr = toUpper(testStr);
	std::string lowerStr = toLower(testStr);
	bool startsWithStr = startsWith(testStr, "Hello");
	bool startsWithInsensitiveStr = startsWith(testStr, "hello", false);
	bool startsWithInsensitiveStr2 = startsWith(testStr, "HELLO", false);
	bool startsWithStr3 = startsWith(testStr, "WORLD", true);
	std::cout << "Original: " << testStr << std::endl;
	std::cout << "Uppercase: " << upperStr << std::endl;
	std::cout << "Lowercase: " << lowerStr << std::endl;
	std::cout << "Starts with 'Hello': " << startsWithStr << std::endl;
	std::cout << "Starts with 'hello' (case insensitive): " << startsWithInsensitiveStr << std::endl;
	std::cout << "Starts with 'HELLO' (case insensitive): " << startsWithInsensitiveStr2 << std::endl;
	std::cout << "Starts with 'WORLD' (case sensitive): " << startsWithStr3 << std::endl;
}
