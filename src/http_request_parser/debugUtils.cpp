/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugUtils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:10:22 by capapes           #+#    #+#             */
/*   Updated: 2025/07/24 12:10:43 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

#define BOLD "\033[1m"
#define GREY "\033[90m"
#define RESET "\033[0m"


std::string title(std::string str)
{
	return BOLD + str + RESET + "\n";
}

std::string keyValue(const std::string& key, const std::string& value) {
	return GREY + key + ": " + RESET + value + "\n";
}

std::ostream& operator<<(std::ostream& os, const Request& request) {
	ControlData controlData = request.getControlData();
	Headers headers = request.getHeaders();
	std::string body = request.getBody();
	Headers::iterator header = headers.begin();
	
	os << title("Control data")
	   << keyValue("Method", controlData.method)
	   << keyValue("Target", controlData.requestTarget)
	   << keyValue("Version", controlData.httpVersion)
	   << title("\nHeaders");
	for (; header != headers.end(); ++header) {
		os << keyValue(header->first, header->second);
	}
	os << title("\nBody")
	   << body;
	return os;
};