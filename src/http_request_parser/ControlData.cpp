/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:24:29 by capapes           #+#    #+#             */
/*   Updated: 2025/07/17 15:16:44 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ControlData.hpp"
#include "FieldValidators.hpp"

void getHeaderFields(const std::string& src, ControlData& _requestControlData)
{
	size_t pos = 0;

	try {
		_requestControlData.method = getField(pos, src, " ");
		_requestControlData.requestTarget = getField(pos, src, " ");
		_requestControlData.httpVersion = getField(pos, src, "\r\n");
	}
	catch (const std::runtime_error& e) {
		_requestControlData.statusCode = 400; // Bad Request
		throw std::runtime_error("Malformed request line: " + std::string(e.what()));
	}
}

ControlData GetRequestControlData(const std::string& src)
{
	ControlData _requestControlData;
	_requestControlData.statusCode = 0;
	
	getHeaderFields(src, _requestControlData);
	isValidMethod(_requestControlData.method, _requestControlData.statusCode);
	isValidRequestTarget(_requestControlData.requestTarget, _requestControlData.statusCode);
	isValidProtocolVersion(_requestControlData.httpVersion, _requestControlData.statusCode);

	std::cout << "Request Control Data Parsed:\n" << _requestControlData << std::endl;
	return _requestControlData;
}

std::ostream& operator<<(std::ostream& os, const ControlData& data)
{
	if (data.statusCode != 0) {
		os << "Error: " << data.statusCode << "\n";
		return os;
	}
	os << "Method: " << data.method << "\n"
	   << "Request Target: " << data.requestTarget << "\n"
	   << "HTTP Version: " << data.httpVersion;
	return os;
}