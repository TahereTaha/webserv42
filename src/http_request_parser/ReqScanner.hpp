/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqScanner.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:58:11 by capapes           #+#    #+#             */
/*   Updated: 2025/12/01 18:39:41 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Request scanner
// Its a utility that works as extractor.
// It receives a string and extracts fields based on delimiters.
// It mantains the current position in the string to allow sequential extraction.
// Flags trim start, trim end, return the strinf with the delimiter included;

#pragma once
#include <string>

class ReqScanner {
public:
	ReqScanner();
	ReqScanner(const std::string& raw);
	~ReqScanner();
	std::string getField(const std::string& delimiter);
	bool		get_ended();
	size_t 		getEndPos(const std::string& delimiter);
	bool		isEndPos();
	void		append(const std::string& raw);
	size_t		getPos() const { return _pos; }
	size_t		getSize() const { return _size; }
	int			find(std::string str) const {
		int pos;
		pos = _raw.find(str);
		return (pos);
	}

private:
	std::string 	_raw;
	size_t 			_pos;
	size_t 			_size;
	bool			_ended;
};
void reqScannerTest();