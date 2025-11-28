/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Schemas.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:03:35 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 20:42:08 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"
#include "Schemas.hpp"


#include "ReqScanner.hpp"


// =====================================================================
// 	Condiional Schemas flags
// =====================================================================
enum SchemaFlags {    
    NONE            = 0,
    LEADING         = 1 << 0,
    TRAILING        = 1 << 1,  
    OPTIONAL_SPACES = (LEADING | TRAILING),
    IS_REQUIRED     = 1 << 2,
};

// =====================================================================
// 	Common schema functions
// =====================================================================
//  - if delimitator instance exist return substring, else empty string
//  - check if its required and runs field validator callback fn
//  - if not valid throws error and set error
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
//      Request
//          |-> ControlData
//          |-> HeadersFields [Iterator] -> HeadersItems
//          |-> Body
// =====================================================================

ControlData validateControlData(const std::string& raw) {
    ReqScanner scanner(raw);
    ControlData result;

    result.method        = extractAndValidate(scanner, controlDataItems[0]);
    result.requestTarget = extractAndValidate(scanner, controlDataItems[1]);
    result.httpVersion   = extractAndValidate(scanner, controlDataItems[2]);
    
    specificControlDataValidation(result.requestTarget);
    return result;
}

Headers validateHeaders(const std::string& raw) {
    Headers     result;
    ReqScanner  scanner(raw);

    while (!scanner.get_ended())  
    {
        std::string field   = extractAndValidate(scanner, headersFields[0]);
        
        ReqScanner  fieldScanner(field);
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
    Request::setActiveRequest(&req);
    Request::setActiveError(0);
    try {
        std::string controlBlock = extractAndValidate(scanner, requestItems[0]);
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