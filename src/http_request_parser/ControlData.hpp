/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:28:37 by capapes           #+#    #+#             */
/*   Updated: 2025/07/17 13:59:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <utils.hpp>

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
// | Invalid HTTP version                  | `505 HTTP Version Not Supported`                                 | HTTP Version Not Supported           | Version not supported by the server.            |


typedef struct s_request_control_data
{
	std::string method;
	std::string requestTarget;
	std::string httpVersion;
	int			statusCode;
}				ControlData;

ControlData GetRequestControlData(const std::string& src);


