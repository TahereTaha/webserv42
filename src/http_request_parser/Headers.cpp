/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:08:42 by capapes           #+#    #+#             */
/*   Updated: 2025/07/17 15:16:50 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers.hpp"
#include "FieldValidators.hpp"


void getHeaderField(const std::string& line, Headers& headers)
{
	size_t pos = 0;
	std::string key = getField(pos, line, ":");
	std::string value = getField(pos, line, "\0");
	
	isValidFieldName(key);
	isValidfieldValue(value);
	if (headers.find(key) != headers.end()) 
		headers[key] += ", " + value;
	else
		headers[key] = value;
}

Headers parseHeaders(const std::string& rawHeaders) {
	
	Headers	headers;
	size_t	pos = 0;
	size_t	endPos;

	endPos = rawHeaders.find(END_OF_HEADERS, pos);
	if (endPos == std::string::npos)
		throw std::runtime_error("Headers block not found in the raw headers");
	while (pos < endPos) 
	{
		std::string line = getField(pos, rawHeaders, END_OF_LINE);
		if (line.empty())
			continue;
		getHeaderField(line, headers);	
	}
	return headers;
}