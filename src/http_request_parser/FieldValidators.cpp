/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:11:28 by capapes           #+#    #+#             */
/*   Updated: 2025/07/17 15:14:18 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"

void isValidFieldName(const std::string& fieldName) {
	if (fieldName.empty() || fieldName.size() > 255) 
		throw std::runtime_error("Invalid field name: " + fieldName);
	for (char c : fieldName)
		if (!isalnum(c) && c != '-' && c != '_') 
			throw std::runtime_error("Invalid field name: " + fieldName);
}

void isValidfieldValue(const std::string& fieldValue) {
	if (fieldValue.empty() || fieldValue.size() > 1024) 
		throw std::runtime_error("Invalid field value: " + fieldValue);
	for (char c : fieldValue)
		if (!isprint(c)) 
			throw std::runtime_error("Invalid field value: " + fieldValue);
}

void isValidMethod(const std::string& method, int &statusCode)
{
	if (method == "GET" || method == "POST");
	else
	{
		statusCode = 501; // Not Implemented
		throw std::runtime_error("Invalid HTTP method: " + method);
	}
}

void isValidProtocolVersion(const std::string& version, int &statusCode)
{
	if (version == "HTTP/1.1" || version == "HTTP/1.0");
	else
	{
		statusCode = 505; // HTTP Version Not Supported
		throw std::runtime_error("Invalid HTTP version: " + version);
	}
}

void isValidRequestTarget(const std::string& target, int &statusCode)
{
	if (target == "*" || !target.empty());
	else
	{
		statusCode = 400; // Bad Request
		throw std::runtime_error("Invalid request target: " + target);
	}
}
