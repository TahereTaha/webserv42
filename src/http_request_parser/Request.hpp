/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:28:40 by capapes           #+#    #+#             */
/*   Updated: 2025/07/22 15:40:56 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

#include <string>
#include "utils.hpp"
#include <stdexcept>
#include <map>

#define END_OF_HEADERS "\r\n\r\n"
#define END_OF_LINE "\r\n"

typedef std::map<std::string, std::string> Headers;

typedef struct ControlData {
	std::string method;
	std::string requestTarget;
	std::string httpVersion;
} ControlData;

typedef struct RequestRawFields {
	std::string controlData;
	std::string headers;
	std::string body;
} RequestRawFields;

class Request {
	public:
		Request(const std::string& rawRequest);
		ControlData getControlData() const { return _controlData; }
		Headers getHeaders() const { return _headers; }
		std::string getBody() const { return _body; }

	private:

		ControlData 	_controlData;
		Headers 		_headers;
		std::string 	_body;
		int 			statusCode;
		

		
		void 						getControlData(std::string& rawControlData);
		void 						getControlDataFields(const std::string& src);
		void 						validateControlData();

		void 						getHeaders(const std::string& rawHeaders);

		void 						parseRequest(const std::string& rawRequest);
		RequestRawFields 			getRequestFields(const std::string& rawRequest);
};

std::ostream& operator<<(std::ostream& os, const Request& request);
