/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:53:34 by capapes           #+#    #+#             */
/*   Updated: 2025/07/28 15:02:03 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <stdexcept>
#include "FieldValidators.hpp"

class Headers {
public:
    Headers();
    Headers(const std::map<std::string, std::string>& vals);
    Headers(const Headers& other);
    Headers	&operator=(const Headers& other);
    ~Headers();

    typedef std::map<std::string, std::string>::iterator iterator;
    typedef std::map<std::string, std::string>::const_iterator const_iterator;

	bool operator==(const Headers& other) const {
		return values == other.values;
	}

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    void 				add(const std::string& key, const std::string& value);
    void 				remove(const std::string& key);

    bool 				has(const std::string& key) const;
    const std::string&	get(const std::string& key) const;
    std::string			&operator[](const std::string& key);

    const std::map<std::string, std::string>& all() const;

private:
    std::map<std::string, std::string> values;
};
