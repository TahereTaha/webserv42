/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Schemas.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:03:35 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 18:46:57 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"
#include "Schemas.hpp"
#include "Request.hpp"
#include "../URI_parsing/URI.hpp"
#include "../URI_parsing/Authority.hpp"
#include "ReqScanner.hpp"


// =====================================================================
// 	Condiional Schemas flags
// =====================================================================
enum SchemaFlags {    
    NONE            = 0,        // No flags
    LEADING         = 1 << 0,
    TRAILING        = 1 << 1,  
    OPTIONAL_SPACES = (LEADING | TRAILING),  // Allow spaces before and after the delimiter
    IS_REQUIRED     = 1 << 2,   // Field is required cannot be empty
};

// =====================================================================
// 	Common schema functions
// =====================================================================

std::string extractAndValidate(ReqScanner &scanner, const SchemaItem& item) {
    std::string value = scanner.getField(item.delimiter, item.flags);
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
//          |-> ControlData
//          |-> Headers
//          |
//          |-> Body
// =====================================================================

static SchemaItem controlDataItems[] = {
    { SP, validMethod, "Invalid HTTP method", 501, IS_REQUIRED },
    { SP, isValidRequest, "Invalid request target", 400, IS_REQUIRED },
    { EOF_, isValidProtocol, "Invalid HTTP version", 505, IS_REQUIRED },
};

static SchemaItem headersItems[] = {
    { ":", isValidKey, "Invalid header key", 400, IS_REQUIRED },
    { EOF_, isValidValue, "Invalid header value", 400, IS_REQUIRED | OPTIONAL_SPACES }
};

static SchemaItem headersFields[] = {
    { END_OF_LINE, NULL, "Invalid header", 400, IS_REQUIRED | TRAILING }
};

static SchemaItem requestItems[] = {
    { END_OF_LINE, NULL, "Invalid request line", 400, IS_REQUIRED}, 
    { END_OF_HEADERS, NULL, "Invalid request", 400, IS_REQUIRED },
    { EOF_, NULL, "Invalid body", 400, NONE }
};


// =====================================================================
// 	STRATEGY VALIDATORS
// =====================================================================

void specificControlDataValidation(const std::string& target)
{
     std::cout << "here: " << target;
    try {	
		URI a = URI(target);
	}
	catch (const std::exception& e)
	{	
        std::cout << "here: ";
		throw std::runtime_error("Invalid URI");
	}
}

ControlData validateControlData(const std::string& raw) {
    ReqScanner scanner(raw);
    ControlData result;


    result.method        = extractAndValidate(scanner, controlDataItems[0]);
    result.requestTarget = extractAndValidate(scanner, controlDataItems[1]);
    result.httpVersion   = extractAndValidate(scanner, controlDataItems[2]);

    return result;
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
    if (headers.has("Content-Length") && !isValidContentLength(headers.get("Content-Length")))
    {
        Request::setActiveError(400);
        throw std::runtime_error("Invalid Content-Length header value");
    }
}

Headers validateHeaders(const std::string& raw) {
    Headers     result;
    ReqScanner  scanner(raw);

    while (!scanner.get_ended())  
    {
        std::string field   = extractAndValidate(scanner, headersFields[0]);
        ReqScanner fieldScanner(field);
        std::string key     = extractAndValidate(fieldScanner, headersItems[0]);
        std::string value   = extractAndValidate(fieldScanner, headersItems[1]);
        result.add(key, value);
        
    }
    specificHeadersValidation(result);
    return result;
}

Request validateRequest(const std::string& raw) {
    Request     req;
    ReqScanner  scanner(raw);

    try {
        std::string controlBlock = extractAndValidate(scanner, requestItems[0]);
        std::cout << controlBlock << std::endl; 
        req.setControlData(validateControlData(controlBlock));

        std::string headers = extractAndValidate(scanner, requestItems[1]);
        headers += END_OF_LINE;
        req.setHeaders(validateHeaders(headers));

        std::string bodyBlock = extractAndValidate(scanner, requestItems[2]);
        req.setBody(bodyBlock);
    }
	catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return req;
	}
  
    return req;
}