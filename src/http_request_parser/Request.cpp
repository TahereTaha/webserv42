/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:31:51 by capapes           #+#    #+#             */
/*   Updated: 2025/07/22 15:53:52 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "FieldValidators.hpp"
#include <iostream>

Request::Request(const std::string& rawRequest) {
	try {
		parseRequest(rawRequest);
	} catch (const std::runtime_error& e) {
		std::cerr << "Error parsing request: " << e.what() << std::endl;	
	}
}

void Request::parseRequest(const std::string& rawRequest) {
	RequestRawFields 	raw;
	
	raw = getRequestFields(rawRequest);
	getControlData(raw.controlData);
	getHeaders(raw.headers);
	_body = raw.body;
}

RequestRawFields Request::getRequestFields(const std::string& rawRequest)
{
	RequestRawFields 	raw;
	size_t 				pos 	= 0;
	
	try 
	{
		raw.controlData = getField(pos, rawRequest, END_OF_LINE);
		raw.headers = getField(pos, rawRequest, END_OF_HEADERS);
		raw.body = rawRequest.substr(pos);
	}
	catch (const std::runtime_error& e) {
		statusCode = 400; // Bad Request
		throw std::runtime_error("Malformed request: " + std::string(e.what()));
	}

	return raw;
}

// =====================================================================
// 								CONTROL DATA
// =====================================================================

void Request::getControlData(std::string& rawControlData)
{
	getControlDataFields(rawControlData);
	validateControlData();
}

void Request::getControlDataFields(const std::string& src)
{
	size_t pos = 0;

	try {
		_controlData.method = getField(pos, src, " ");
		_controlData.requestTarget = getField(pos, src, " ");
		_controlData.httpVersion = src.substr(pos);
	}
	catch (const std::runtime_error& e) {
		statusCode = 400; // Bad Request
		throw std::runtime_error("Malformed request line: " + std::string(e.what()));
	}
}

void Request::validateControlData()
{
	isValidMethod(_controlData.method, statusCode);
	isValidRequestTarget(_controlData.requestTarget, statusCode);
	isValidProtocolVersion(_controlData.httpVersion, statusCode);
}

// =====================================================================
// 								HEADERS
// =====================================================================

#define headerPair std::pair<std::string, std::string>


inline void addFieldToHeaders(headerPair &pair, Headers& headers)
{
	std::string key 		= pair.first;
	std::string value 	= pair.second;

	if (headers.find(key) != headers.end())
		headers[key] += ", " + value;
	else
		headers[key] = value;
}

inline headerPair getHeaderField(const std::string& line)
{
	size_t 		pos 	= 0;
	headerPair 	pair;

	pair.first 	= getField(pos, line, ":");
	pair.second = line.substr(pos);
	
	isValidHeaderKey(pair.first);
	isValidHeaderValue(pair.second);
	return pair;
}

void addFieldsToHeaders(std::string rawHeaders, Headers& _headers)
{
	std::string	line;
	headerPair	pair;
	size_t 		pos 		= 0;
	size_t 		endPos 		= rawHeaders.length();

	rawHeaders += END_OF_LINE;
	while (pos < endPos) {
		line = getField(pos, rawHeaders, END_OF_LINE);
		if (line.empty())
			continue;
		pair = getHeaderField(line);
		addFieldToHeaders(pair, _headers);
	}
}

void Request::getHeaders(const std::string& rawHeaders)
{
	try {
		addFieldsToHeaders(rawHeaders, _headers);
	} catch (const std::runtime_error& e) {
		statusCode = 400; // Bad Request
		throw std::runtime_error("Error parsing headers: " + std::string(e.what()));
	}
}


#define BOLD "\033[1m"
#define GREY "\033[90m"
#define RESET "\033[0m"


std::string title(std::string str)
{
	return BOLD + str + RESET + "\n";
}

std::string keyValue(const std::string& key, const std::string& value) {
	return GREY + key + ": " + RESET + value + "\n";
}

std::ostream& operator<<(std::ostream& os, const Request& request) {
	ControlData controlData = request.getControlData();
	Headers headers = request.getHeaders();
	std::string body = request.getBody();
	Headers::iterator header = headers.begin();
	
	os << title("Control data")
	   << keyValue("Method", controlData.method)
	   << keyValue("Target", controlData.requestTarget)
	   << keyValue("Version", controlData.httpVersion)
	   << title("\nHeaders");
	for (; header != headers.end(); ++header) {
		os << keyValue(header->first, header->second);
	}
	os << title("\nBody")
	   << body;
	return os;
};