/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Schemas.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:03:35 by capapes           #+#    #+#             */
/*   Updated: 2025/11/27 22:01:05 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"
#include "Schemas.hpp"
#include "Request.hpp"
#include <limits.h>
#include "../URI_parsing/Authority.hpp"


// =====================================================================
// 	Condiional Schemas flags
// =====================================================================
enum SchemaFlags {    
    NONE            = 0,        // No flags
    OPTIONAL_SPACES = 1 << 0,   // Allow spaces before and after the delimiter
    IS_REQUIRED     = 1 << 1,   // Field is required cannot be empty
};

// =====================================================================
// 	Common schema functions
// =====================================================================

std::string remove_trailing(const std::string& str, const std::string& chars = " \t\r\n")
{
    size_t end = str.find_last_not_of(chars);
    if (end == std::string::npos)
        return "";
    return str.substr(0, end + 1);
}

std::string remove_leading(const std::string& str, const std::string& chars = " \t\r\n")
{
    size_t start = str.find_first_not_of(chars);
    if (start == std::string::npos)
        return "";
    return str.substr(start);
}

inline std::string getField(size_t& pos,
                            const std::string& raw,
                            const std::string& delimiter,
                            bool optionalSpaces = false)
{
    size_t endPos = raw.find(delimiter, pos);

    if (endPos == std::string::npos)
        return ("");
    if (delimiter == EOL)
        endPos = raw.size();
    std::string field = raw.substr(pos, endPos - pos);
    pos = endPos + delimiter.size();
    if (optionalSpaces)
    {
        field = remove_leading(field);
        field = remove_trailing(field);
    }

    return field;
}


std::string extractAndValidate(size_t& pos, const std::string& raw, const SchemaItem& item) {
    std::string value = getField(pos, raw, item.delimiter, item.flags);
    if ((item.flags & IS_REQUIRED && value.empty()) || (item.fn && !item.fn(value)))
    {
        Request::setActiveError(item.errorCode);
        throw std::runtime_error(item.error);
    }
    return value;
}


// =====================================================================
// 	SCHEMAS
// =====================================================================
//      Request
//          |-> Header
//          |       |-> ControlData
//          |       |-> Headers
//          |
//          |-> Body
// =====================================================================

static SchemaItem controlDataItems[] = {
    { SP, validMethod, "Invalid HTTP method", 501, IS_REQUIRED },
    { SP, isValidRequest, "Invalid request target", 400, IS_REQUIRED },
    { EOL, isValidProtocol, "Invalid HTTP version", 505, IS_REQUIRED },
};

static SchemaItem headersItems[] = {
    { ":", isValidKey, "Invalid header key", 400, IS_REQUIRED },
    { END_OF_LINE, isValidValue, "Invalid header value", 400, IS_REQUIRED | OPTIONAL_SPACES }
};

static SchemaItem HeaderBlock[] = {
	{ END_OF_LINE, NULL, "Invalid request line", 400, IS_REQUIRED},
	{ EOL, NULL, "Invalid headers", 400, IS_REQUIRED },
};

static SchemaItem requestItems[] = {
    { END_OF_HEADERS, NULL, "Invalid request", 400, IS_REQUIRED },
    { "", NULL, "Invalid body", 400, NONE }
};


// =====================================================================
// 	STRATEGY VALIDATORS
// =====================================================================

ControlData validateControlData(const std::string& raw) {
    ControlData result;
    size_t pos = 0;

    result.method        = extractAndValidate(pos, raw, controlDataItems[0]);
    result.requestTarget = extractAndValidate(pos, raw, controlDataItems[1]);
    result.httpVersion   = extractAndValidate(pos, raw, controlDataItems[2]);

    return result;
}

long string_to_long(const std::string& s, size_t* pos = 0, int base = 10) {
    char* end;
    errno = 0;
    long result = std::strtol(s.c_str(), &end, base);

    if (pos) {
        *pos = end - s.c_str();
    }
    if (errno == ERANGE || result > LONG_MAX || result < LONG_MIN) {
        throw std::out_of_range("string_to_long: value out of range");
    }
    if (end == s.c_str()) {
        throw std::invalid_argument("string_to_long: no conversion could be performed");
    }
    return result;
}

bool isValidContentLength(const std::string& contentLength) {
    if (contentLength.empty()) return false;
    std::string::const_iterator it = contentLength.begin();
    for (;it != contentLength.end(); ++it) {
        if (!isdigit(*it)) {
            Request::setActiveError(400);
            throw std::runtime_error("Invalid Content-Length header value");
        }
    }
    long length = string_to_long(contentLength);
    return length >= 0 && length <= INT_MAX;
}

void specificHeadersValidation(Headers& headers)
{
    // Check if it has contnt lenght only when has body and encoding
    if (headers.has("Host") == false)
    {
        Request::setActiveError(400);
        throw std::runtime_error("Missing Host or Content-Lenght header");
    }
    try 
    {
        Authority hostURI = Authority(headers.get("Host"));
    }
    catch (const std::exception& e)
    { 
        Request::setActiveError(400);
        throw std::runtime_error("Invalid Host header value URI");
    }
    std::string contentLength = headers.get("Content-Length");
    if (contentLength != "" && !isValidContentLength(contentLength))
    {
        Request::setActiveError(400);
        throw std::runtime_error("Invalid Content-Length header value");
    }
}

Headers validateHeaders(const std::string& raw) {
    Headers result;

    size_t pos = 0;
    while (pos < raw.size())  
    {
        if (raw[pos] == '\r' || raw[pos] == '\n') {
            pos++;
            continue;
        }
        std::string key   = extractAndValidate(pos, raw, headersItems[0]);
        std::string value = extractAndValidate(pos, raw, headersItems[1]);
        result.add(key, value);
    }
    specificHeadersValidation(result);
    return result;
}

Request validateRequest(const std::string& raw) {
    Request req;
    size_t 	pos 			= 0;
	size_t 	headerPos 		= 0;

    Request::setActiveRequest(&req);
    Request::setActiveError(0);
    try {
        std::string headers = extractAndValidate(pos, raw, requestItems[0]);
        headers += END_OF_LINE;

        std::string controlBlock = extractAndValidate(headerPos, headers, HeaderBlock[0]);
        req.setControlData(validateControlData(controlBlock));

        std::string headersBlock = extractAndValidate(headerPos, headers, HeaderBlock[1]);
        headersBlock.append(END_OF_LINE);
        req.setHeaders(validateHeaders(headersBlock));

        std::string bodyBlock = extractAndValidate(pos, raw, requestItems[1]);
        req.setBody(bodyBlock);
        
    }
	catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return req;
	}
  
    return req;
}