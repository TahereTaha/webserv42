/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:11:28 by capapes           #+#    #+#             */
/*   Updated: 2025/07/30 17:56:25 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldValidators.hpp"
#include <iostream>

// =====================================================================
// 					GENERIC FIELD VALIDATORS
// =====================================================================

inline bool isValidLength(const std::string& str, size_t maxLength, size_t minLength) {
    return !(str.empty() || str.size() > maxLength || str.size() < minLength);
}

inline bool isValidCharSet(const std::string& str, bool (*fn)(const char& c)) {
    for (size_t i = 0; i < str.size(); ++i)
        if (!fn(str[i])) return false;
    return true;
}

// =====================================================================
// 					KEYS AND VALUES VALID CHARACTERS
// =====================================================================
inline bool keyValidChar(const char& c) {
	return isalnum(c) || c == '-' || c == '_';
}

inline bool valueValidChar(const char& c) {
	return isprint(c) && c != '\r' && c != '\n' && c != ':';
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
