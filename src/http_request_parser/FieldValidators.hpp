/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:58:15 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 17:57:46 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <string>
#include <cstdlib>   // for std::strtol
#include <cerrno>    // for errno, ERANGE


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

bool isValidKey(const std::string& key);
bool isValidValue(const std::string& value);
bool validMethod(const std::string& method);
bool isValidRequest(const std::string& target);
bool isValidProtocol(const std::string& version);
bool string_to_long(const std::string& s, size_t* pos, int base);
bool isValidContentLength(const std::string& contentLength);
