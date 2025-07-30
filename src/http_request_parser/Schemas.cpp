/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Schemas.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:03:35 by capapes           #+#    #+#             */
/*   Updated: 2025/07/30 18:12:27 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"
#include "Schemas.hpp"
#include "Request.hpp"


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


inline std::string getField(size_t& pos, const std::string& raw, const std::string& delimiter)
{
	if (delimiter.empty())
		return raw.substr(pos);
	size_t endPos = raw.find(delimiter, pos);
	if (endPos == std::string::npos)
		return ("");
	std::string field = raw.substr(pos, endPos - pos);
	pos = endPos + delimiter.size();
    field = remove_leading(field);
    field = remove_trailing(field);
    if (field.empty())
    {
        return "";
    }
	return field;
}

std::string extractAndValidate(size_t& pos, const std::string& raw, const SchemaItem& item) {
    std::string value = getField(pos, raw, item.delimiter);

    if (!item.isRequired && value.empty())
        return value;
    if (item.fn && !item.fn(value))
    {
        Request::setActiveError(item.errorCode);
        throw std::runtime_error(item.error);
    }
    if (value.empty() && item.isRequired)
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
    { SP, validMethod, "Invalid HTTP method", 501, true },
    { SP, isValidRequest, "Invalid request target", 400, true },
    { "", isValidProtocol, "Invalid HTTP version", 505, true }
};

static SchemaItem headersItems[] = {
    { ":", isValidKey, "Invalid header key", 400, true },
    { END_OF_LINE, isValidValue, "Invalid header value", 400, true }
};

static SchemaItem HeaderBlock[] = {
	{ END_OF_LINE, NULL, "Invalid request line", 400, true },
	{ "", NULL, "Invalid headers", 400, false },
};

static SchemaItem requestItems[] = {
    { END_OF_HEADERS, NULL, "Invalid request", 400, true },
    { "", NULL, "Invalid body", 400, false }
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

Headers validateHeaders(const std::string& raw) {
    Headers result;
    if (raw.empty()) return result;

    size_t pos = 0;
    while (pos < raw.size())  
    {
        std::string key   = extractAndValidate(pos, raw, headersItems[0]);
        std::string value = extractAndValidate(pos, raw, headersItems[1]);
        result.add(key, value);
    }
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
        headers += END_OF_LINE; // Ensure headers end with a newline

        std::string controlBlock = extractAndValidate(headerPos, headers, HeaderBlock[0]);
        req.setControlData(validateControlData(controlBlock));

        std::string headersBlock = extractAndValidate(headerPos, headers, HeaderBlock[1]);
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