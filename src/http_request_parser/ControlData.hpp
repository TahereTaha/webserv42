/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:36:50 by capapes           #+#    #+#             */
/*   Updated: 2025/07/24 14:42:05 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "utils.hpp"
#include <stdexcept>
#include "FieldValidators.hpp"
#include "Request.hpp"
#include <map>
#include <vector>

typedef struct ControlData {
	std::string method;
	std::string requestTarget;
	std::string httpVersion;
} ControlData;


typedef std::vector<std::string> delimiter;



typedef bool (*validator)(const std::string&);

typedef struct 			s_schemaItem {
	delimiter 			delimiters;
	validator 			fn;
    std::string 		error;
    int 				errorCode;
} 						t_schemaItem;

typedef std::map<std::string, t_schemaItem> RequestSchema;


bool validMethod(const std::string& method) {
	return method == "GET" || method == "POST" || method == "PUT" || method == "DELETE";
}

bool isValidRequest(const std::string& target) {
	// For simplicity, let's assume a valid request target is a non-empty string
	return !target.empty();
}

bool isValidProtocol(const std::string& version) {
	// A simple check for HTTP/1.1 or HTTP/2.0
	return version == "HTTP/1.1" || version == "HTTP/2.0";
}

#define EOL	"\0"
#define SP	" "
#define TB	"\t"

RequestSchema getControlDataSchema()
{
	static RequestSchema validators;

	if (validators.size() > 0) {
		return validators;
	}
	
	t_schemaItem 			method;
	method.fn 				= validMethod;
	method.delimiters 		= {SP, TB};
	method.error 			= "Invalid HTTP method";
	method.errorCode 		= 501;
	validators["method"] 	= method;

	t_schemaItem 			target;
	target.fn 				= isValidRequest;
	target.delimiters 		= {SP, TB};
	target.error 			= "Invalid request target";
	target.errorCode 		= 400;
	validators["target"] 	= target;
	
	t_schemaItem 			version;
	version.fn 				= isValidProtocol;
	version.delimiters		= {EOL};
	version.error 			= "Invalid HTTP version";
	version.errorCode 		= 505;
	validators["version"] 	= version;
	
	return validators;
}

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

bool keyValidChar(const char& c) {
	return isalnum(c) || c == '-' || c == '_';
}

bool isValidKey(const std::string& key) {
	
	isValidLength(key, 256, 1);
	isValidCharSet(key, keyValidChar);
}

RequestSchema getHeadersFieldsSchema()
{
	static RequestSchema validators;

	if (validators.size() > 0) {
		return validators;
	}

	t_schemaItem 			key;
	key.fn 					= isValidKey;
	key.delimiters 			= {":"};
	key.error 				= "Invalid header key";
	key.errorCode 			= 400;
	validators["key"] 		= key;

	t_schemaItem 			value;
	value.fn 				= isValidKey;
	value.delimiters 		= {EOL};
	value.error 			= "Invalid header value";
	value.errorCode 		= 400;
	validators["value"] 	= value;

	return validators;
}


std::string getSchemaItem(t_schemaItem schemap, const std::string& raw)
{
	size_t		pos		= 0;
	std::string field	= getField(pos, raw, schemap.delimiters[0]);
	int 		errorCode;
	if (schemap.fn(field))
	{
		errorCode = schemap.errorCode;
		throw std::runtime_error(schemap.error + ": " + field);
	}
	return field;
}


RequestSchema getRequestSchema()
{
	static RequestSchema validators;

	if (validators.size() > 0) {
		return validators;
	}

	t_schemaItem 					controlData;
	controlData.fn 					= NULL;
	controlData.delimiters 			= {END_OF_LINE};
	controlData.error 				= "Invalid request format";
	controlData.errorCode 			= 400;
	validators["controlData"] 		= controlData;

	t_schemaItem 					headers;
	headers.fn 						= isValidRequest;
	headers.delimiters 				= {END_OF_HEADERS};
	headers.error 					= "Invalid headers format";
	headers.errorCode 				= 400;
	validators["headers"] 			= headers;

	t_schemaItem 					body;
	body.fn 						= isValidRequest;
	body.delimiters 				= {EOL};
	body.error 						= "Invalid body format";
	body.errorCode 					= 400;
	validators["body"] 				= body;
	
	return validators;
}


// HTTP generic parser
// Recives a raw string
// split it into n fields with a pattern of validators
// validate each field with the corresponding validator
// if necesary transform the field into a specific type




