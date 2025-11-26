/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:05:08 by capapes           #+#    #+#             */
/*   Updated: 2025/11/26 17:14:24 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers.hpp"

Headers::Headers() {}

Headers::Headers(const std::map<std::string, std::string>& vals)
    : values(vals) {}

Headers::Headers(const Headers& other)
    : values(other.values) {}

Headers &Headers::operator=(const Headers& other) {
    if (this != &other)
        values = other.values;
    return *this;
}

Headers::~Headers() {}

Headers::iterator Headers::begin() { return values.begin(); }
Headers::iterator Headers::end() { return values.end(); }
Headers::const_iterator Headers::begin() const { return values.begin(); }
Headers::const_iterator Headers::end() const { return values.end(); }

void Headers::add(const std::string& key, const std::string& value) {
    if (!isValidKey(key))
        throw std::runtime_error("Invalid header key: " + key);
    if (!isValidValue(value))
        throw std::runtime_error("Invalid header value for key: " + key);
    values[key] = value;
}

void Headers::remove(const std::string& key) {
    values.erase(key);
}

bool Headers::has(const std::string& key) const {
    return values.find(key) != values.end();
}

const std::string& Headers::get(const std::string& key) const {
    std::map<std::string, std::string>::const_iterator it = values.find(key);
    if (it != values.end())
        return it->second;
    static const std::string empty = "";
    return empty;
}

std::string& Headers::operator[](const std::string& key) {
    if (!isValidKey(key))
        throw std::runtime_error("Invalid header key: " + key);
    return values[key];
}
