/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:11:28 by capapes           #+#    #+#             */
/*   Updated: 2025/07/24 14:30:08 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"


// =====================================================================
// 					GENERIC FIELD VALIDATORS
// =====================================================================
void isValidLength(const std::string& str, size_t maxLength, size_t minLength) {
	if (str.empty() || str.size() > maxLength || str.size() < minLength)
		throw std::runtime_error("Invalid field name: " + str);
}

void isValidCharSet(const std::string& str, bool (*fn)(const char &c)) {
	for (size_t i = 0; i < str.size(); ++i) {
		if (!fn(str[i]))
			throw std::runtime_error("Invalid character in field: " + str);
	}
}

// =====================================================================
// 					KEYS AND VALUES VALID CHARACTERS
// =====================================================================
bool keyValidChar(const char& c) {
	return isalnum(c) || c == '-' || c == '_';
}

bool valueValidChar(const char& c) {
	return isprint(c);
}

// =====================================================================
// 					VALIDATORS FOR REQUEST HEADERS FIELDS
// =====================================================================
void isValidHeaderKey(const std::string& headerKey) {
	isValidLength(headerKey, 256, 1);
	isValidCharSet(headerKey, keyValidChar);
}

void isValidHeaderValue(const std::string& headerValue) {
	isValidLength(headerValue, 8192, 1);
	isValidCharSet(headerValue, valueValidChar);
}

// =====================================================================
// 					VALIDATORS FOR CONTROL DATA FIELDS
// =====================================================================

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
