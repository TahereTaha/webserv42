/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:58:14 by capapes           #+#    #+#             */
/*   Updated: 2025/07/22 15:41:51 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <iostream>

int main() {
	std::string rawRequest = "GET /index.html HTTP/1.1\r\n"
							 "Host: www.example.com\r\n"
							 "User-Agent: curl/7.64.1\r\n"
							 "Accept: */*\r\n"
							 "\r\n";

	Request request(rawRequest);
	std::cout << request << std::endl;
	
	return 0;
}