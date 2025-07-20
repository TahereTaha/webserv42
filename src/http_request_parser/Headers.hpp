/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:59:34 by capapes           #+#    #+#             */
/*   Updated: 2025/07/17 15:16:59 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <string>
#include <utils.hpp>
#include <stdexcept>
#include <map>

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


#define END_OF_HEADERS "\r\n\r\n"
#define END_OF_LINE "\r\n"

typedef std::map<std::string, std::string> Headers;

Headers parseHeaders(const std::string& rawHeaders);