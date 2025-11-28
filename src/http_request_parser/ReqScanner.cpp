/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqScanner.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:02:01 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 14:51:31 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReqScanner.hpp"

ReqScanner::ReqScanner(const std::string& raw)
	: _raw(raw), _pos(0) {}

#define LEADING 1
#define TRAILING 1 << 1
#define OPTIONAL_SPACES (LEADING | TRAILING)
#define SPACES " \t\n\r\f\v"

std::string trim(std::string& str, int flags, size_t start, size_t end)
{
	size_t length = end - start;
	
	if (flags | LEADING)
		start = str.find_first_not_of(SPACES, start, length);
    if (start == std::string::npos)
        return ("");
	if (flags | TRAILING)
    	end = str.find_last_not_of(SPACES, end - 1, length) + 1;
    return (str.substr(start, end - start));
}


std::string ReqScanner::getField(const std::string& delimiter) {		
	
	size_t 			end;
	std::string 	field = "";
	
	if (_ended)
		return ("");
	
	end = delimiter == EOF
		? _raw.size()
		: _raw.find(delimiter, _pos);
					
	_ended = end == std::string::npos;
	
	if (_ended)
		field = "";
	else
	{
		field =_raw.substr(_pos, end - _pos);				
		_pos = end + delimiter.size();
	}
	return (field);
}


// if (!flags)
// 		return (field);
		
// 	if (flags | LEADING)
// 		start = ignore_spaces(start, LEADING);
// 	if (flags | TRAILING)
// 		end = ignore_spaces(end, TRAILING);
// 	if (start == -1 || end == -1 || start == end)
// 		return ("");
// 	return (field.substr(start, end - start));


// Previous get field function 

// std::string remove_trailing(const std::string& str, const std::string& chars = " \t\r\n")
// {
//     size_t end = str.find_last_not_of(chars);
//     if (end == std::string::npos)
//         return "";
//     return str.substr(0, end + 1);
// }

// std::string remove_leading(const std::string& str, const std::string& chars = " \t\r\n")
// {
//     size_t start = str.find_first_not_of(chars);
//     if (start == std::string::npos)
//         return "";
//     return str.substr(start);
// }

// inline std::string getField(size_t& pos,
//                             const std::string& raw,
//                             const std::string& delimiter,
//                             bool optionalSpaces = false)
// {
//     size_t endPos = raw.find(delimiter, pos);

//     if (endPos == std::string::npos)
//         return ("");
//     if (delimiter == EOL)
//         endPos = raw.size();
//     std::string field = raw.substr(pos, endPos - pos);
//     pos = endPos + delimiter.size();
//     if (optionalSpaces)
//     {
//         field = remove_leading(field);
//         field = remove_trailing(field);
//     }

//     return field;
// }