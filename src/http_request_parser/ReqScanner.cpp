/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqScanner.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:02:01 by capapes           #+#    #+#             */
/*   Updated: 2025/12/03 18:03:31 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReqScanner.hpp"
#include "Schemas.hpp"

#define NOT_FOUND std::string::npos

ReqScanner::ReqScanner(const std::string& raw)
	: _raw(raw), _pos(0), _ended(false)
{
	_size = _raw.size();
	if (_size == 0)
		_pos = NOT_FOUND;
}

ReqScanner::~ReqScanner() {}

size_t ReqScanner::getEndPos(const std::string& delimiter)
{
	size_t res;

	delimiter == EOF_ 
		? res = _size
		: res = _raw.find(delimiter, _pos);

	return res;
}

inline bool ReqScanner::isEndPos()
{
	return (_pos == NOT_FOUND || _pos >= _size);
}

std::string ReqScanner::getField(const std::string& delimiter) 
{		
	if (isEndPos())
		return EMPTY_STRING;	

	size_t		start 	= _pos;
	size_t		end		= getEndPos(delimiter);
	std::string field 	= EMPTY_STRING; 

	if (end != NOT_FOUND && end != start)
		field = _raw.substr(start, end - start);
	_pos = end + delimiter.size();
	return field;
}

