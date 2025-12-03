/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:11:28 by capapes           #+#    #+#             */
/*   Updated: 2025/12/01 18:11:27 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"

// =====================================================================
// 					GENERIC FIELD VALIDATORS
// =====================================================================
inline bool isValidLength(const std::string& str, size_t maxLength, size_t minLength) {
    return !(str.empty() || str.size() > maxLength || str.size() < minLength);
}

inline bool isValidCharSet(const std::string& str, bool (*fn)(const char& c)) {
    for (size_t i = 0; i < str.size(); i++)
        if (!fn(str[i])) return false;
    return true;
}

// =====================================================================
// 					KEYS AND VALUES VALID CHARACTERS
// =====================================================================
inline bool keyValidChar(const char& c) {
	return isalnum(c) || c == '-' || c == '_';
}

// TO DO replace for localhost:8080 remove c != ':'
inline bool valueValidChar(const char& c) {
	return isprint(c) && c != '\r' && c != '\n';
}

// =====================================================================
// 					VALIDATORS FOR REQUEST HEADERS FIELDS
// =====================================================================
bool isValidKey(const std::string& key) {
	return 	isValidLength(key, 256, 1) && isValidCharSet(key, keyValidChar);
}

bool isValidValue(const std::string& value) {
	return isValidLength(value, 8192, 1) && isValidCharSet(value, valueValidChar);
}

// =====================================================================
// 					VALIDATORS FOR CONTROL DATA FIELDS
// =====================================================================

bool validMethod(const std::string& method) {
	return method == "GET" || method == "POST" || method == "PUT" || method == "DELETE";
}

bool isValidRequest(const std::string& target) {
	return !target.empty();
}

bool isValidProtocol(const std::string& version) {
	return version == "HTTP/1.1" || version == "HTTP/2.0";
}

// =====================================================================
// 					VALIDATORS FOR HEADER FIELDS
// =====================================================================
bool string_to_long(const std::string& s, size_t* pos = 0, int base = 10) {
    char* end;
    errno = 0;
    long result = std::strtol(s.c_str(), &end, base);

    if (pos) {
        *pos = end - s.c_str();
    }
    if (errno == ERANGE || result > LONG_MAX || result < LONG_MIN) {
		return false;
    }
    if (end == s.c_str()) {
        return false;
    }
    return result >= 0 && result <= INT_MAX;
}

bool isValidContentLength(const std::string& s) {
     if (s.empty()) return false;

    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
        if (!isdigit(*it))
            return false;
    }

    unsigned long value = 0;

    for (size_t i = 0; i < s.size(); ++i) {
        int digit = s[i] - '0';
        if (value > (ULONG_MAX - digit) / 10)
            return false;

        value = value * 10 + digit;
    }
    return value <= INT_MAX;
}

int atoi_safe(const std::string& str) {
    size_t pos = 0;
    long result = std::strtol(str.c_str(), NULL, 10);

    if (pos == 0 || result < INT_MIN || result > INT_MAX) {
        return -1;
    }
    return static_cast<int>(result);
}


// =====================================================================
// 	ODDLY SPECIFIC VALIDATORS VALIDATORS
// =====================================================================
void specificControlDataValidation(const std::string& target)
{
    try {	
		URI a = URI(target);
	}
	catch (const std::exception& e)
	{	
        Request::setActiveError(400);
		throw std::runtime_error("Invalid URI");
	}
}

// [ TO DO ] Check if it has content lenght only when has body and encoding
void specificHeadersValidation(Headers& headers)
{
    if (headers.has("Content-Length") && !isValidContentLength(headers.get("Content-Length")))
    {
        Request::setActiveError(400);
        throw std::runtime_error("Invalid Content-Length header value");
    }
    
    if (headers.has("Host"))
    {
        try 
        {
            Authority hostURI = Authority(headers.get("Host"));
        }
        catch (const std::exception& e)
        { 
			Request::setActiveError(400);
            throw std::runtime_error("Invalid Host header value URI");
        }
    }
    else
    {   
        throw std::runtime_error("Missing Host or Content-Lenght header");
    }
}
