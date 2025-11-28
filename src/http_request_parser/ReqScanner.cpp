/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqScanner.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:02:01 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 10:18:51 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReqScanner.hpp"

ReqScanner::ReqScanner(const std::string& raw)
	: _raw(raw), _pos(0) {}

#define LEADING 1
#define TRAILING 1 << 1
#define OPTIONAL_SPACES (LEADING | TRAILING)
#define SPACES " \t\n\r\f\v"

std::string ReqScanner::getField(const std::string& delimiter, unsigned int optionalSpaces = 0) {
	size_t 		endPos;
	std::string field;

	if (optionalSpaces | LEADING)
		_pos = _raw.find_first_not_of(SPACES, _pos);
 	endPos = _raw.find(delimiter, _pos);
	if (endPos == std::string::npos)
		return ("");
	if (optionalSpaces & TRAILING)
		endPos = _raw.find_last_not_of(SPACES, endPos - 1) + 1;
	field = _raw.substr(_pos, endPos - _pos);
	_pos = endPos + delimiter.size();
	return field;
}

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