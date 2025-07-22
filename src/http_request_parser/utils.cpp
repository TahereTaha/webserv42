/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:20:20 by capapes           #+#    #+#             */
/*   Updated: 2025/07/20 18:06:33 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// documentation


#include <stdexcept>

// Function to extract a field from the request line based on the given delimiter
std::string getField(size_t& pos, const std::string& src, const std::string& delimiter)
{
	size_t nextPos = src.find(delimiter, pos);
	if (nextPos == std::string::npos)
		throw std::runtime_error("Delimiter not found in the string");
	std::string field = src.substr(pos, nextPos - pos);
	pos = nextPos + delimiter.length();
	return field;
}
