/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:20:20 by capapes           #+#    #+#             */
/*   Updated: 2025/07/24 14:26:07 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// documentation


#include <stdexcept>

std::string getField(size_t& pos, const std::string& src, const std::string& delimiter)
{
	size_t nextPos = src.find(delimiter, pos);
	if (nextPos == std::string::npos)
		throw std::runtime_error("Delimiter not found in the string");
	std::string field = src.substr(pos, nextPos - pos);
	pos = nextPos + delimiter.length();
	return field;
}
