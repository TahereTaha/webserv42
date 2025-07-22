/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:11:28 by capapes           #+#    #+#             */
/*   Updated: 2025/07/22 15:19:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"

void isValidHeaderKey(const std::string& headerKey) {
	if (headerKey.empty() || headerKey.size() > 255) 
		throw std::runtime_error("Invalid field name: " + headerKey);
	for (size_t i = 0; i < headerKey.size(); ++i)
		if (!isalnum(headerKey[i]) && headerKey[i] != '-' && headerKey[i] != '_') 
			throw std::runtime_error("Invalid field name: " + headerKey);
}

void isValidHeaderValue(const std::string& headerValue) {
	if (headerValue.empty() || headerValue.size() > 1024) 
		throw std::runtime_error("Invalid field value: " + headerValue);
	for (size_t i = 0; i < headerValue.size(); ++i)
		if (!isprint(headerValue[i])) 
			throw std::runtime_error("Invalid field value: " + headerValue);
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
