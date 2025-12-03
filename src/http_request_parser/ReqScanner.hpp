/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqScanner.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:58:11 by capapes           #+#    #+#             */
/*   Updated: 2025/12/03 18:03:02 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Request scanner
// Its a utility that works as extractor.
// It receives a string and extracts fields based on delimiters.
// It mantains the current position in the string to allow sequential extraction.
// Flags trim start, trim end, return the strinf with the delimiter included;

#pragma once
#include <string>

class ReqScanner
{
public:
	ReqScanner(const std::string& raw);
	~ReqScanner();

	std::string getField(const std::string& delimiter);
	size_t 		getEndPos(const std::string& delimiter);
	bool		isEndPos();

private:
	std::string 	_raw;
	size_t 			_pos;
	size_t 			_size;
	bool			_ended;
};
