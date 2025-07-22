/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:15:06 by capapes           #+#    #+#             */
/*   Updated: 2025/07/22 14:47:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <string>


// ABNF: https://datatracker.ietf.org/doc/html/rfc9110#section-9.3
// control data to describe and route the message
// Request message control data includes a request method, request target, and protocol version -> 1 line -> 3 tokens

// start-line     = request-line 
// request-line   = method SP request-target SP HTTP-version CRLF
// method         = "GET" | "POST"
// request-target  = "*" | absolute-URI | authority | path-abempty
// HTTP-version   = "HTTP" "/" 1*DIGIT "." 1*DIGIT


// | **Failure**                           | **HTTP Status Code**                                             | **Reason Phrase**                    | **Explanation**                                 |
// | ------------------------------------- | ---------------------------------------------------------------- | ------------------------------------ | ----------------------------------------------- |
// | Missing or malformed request line     | `400 Bad Request`                                                | Bad Request                          | Server couldn't understand the request.         |
// | Invalid HTTP method                   | `501 Not Implemented`                                            | Not Implemented                      | Method is unrecognized or unsupported.          |
// | Invalid HTTP version                  | `505 HTTP Version Not Supported`    

// ABNF: https://datatracker.ietf.org/doc/html/rfc9110#section-9.3

// Headers are key-value pairs that provide additional information about the request or response.
// header-field   = field-name ":" OWS field-value OWS
// field-name     = token
// field-value    = *( field-content / obs-fold )
// field-content  = field-vchar [ 1*( SP / HTAB ) field-vchar ]
// field-vchar    = VCHAR / obs-text
// obs-fold       = CRLF 1*( SP / HTAB )
// obs-text       = %x80-FF
// token          = 1*tchar
// tchar          = "!" / "#" / "$" / "%" / "&" / "'" / "*"
//                 / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~"
//                 / DIGIT / ALPHA
// OWS            = *( SP / HTAB )
// VCHAR          = %x21-7E
// CRLF           = %x0D %x0A



void isValidHeaderKey(const std::string& HeaderKey);
void isValidHeaderValue(const std::string& HeaderValue);
void isValidMethod(const std::string& method, int &statusCode);
void isValidProtocolVersion(const std::string& version, int &statusCode);
void isValidRequestTarget(const std::string& target, int &statusCode);
