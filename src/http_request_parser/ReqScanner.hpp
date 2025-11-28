/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqScanner.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:58:11 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 10:16:13 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Request scanner
// Its a utility that works as extractor.
// It receives a string and extracts fields based on delimiters.
// It mantains the current position in the string to allow sequential extraction.

#pragma once
#include <string>

class ReqScanner {
public:
	ReqScanner(const std::string& raw);
	std::string getField(const std::string& delimiter, unsigned int optionalSpaces = 0);
	bool isEnd() const;

private:
	std::string _raw;
	size_t _pos;
};