/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugUtils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:10:22 by capapes           #+#    #+#             */
/*   Updated: 2025/07/30 18:09:04 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <iostream>

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
