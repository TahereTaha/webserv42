/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTerminalVector.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 01:29:21 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 09:31:45 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TypeTerminalVector.hpp"

TerminalVector::TerminalVector() {
	match = nullptr;
}

TerminalVector::~TerminalVector()
{
	for (TerminalIterator it = this->contents.begin(); it != this->contents.end(); ++it)
		delete *it;
}

void TerminalVector::setAll(std::string content)
{
	int longestLength = 0;
	match = nullptr;
	for (TerminalIterator it = this->contents.begin(); it != this->contents.end(); ++it)
	{
		(*it)->setText(content);
		if ((*it)->length() > longestLength)
		{
			longestLength = (*it)->length();
			match = *it;
		}
	}
}

void TerminalVector::print()
{
	for (TerminalIterator it = this->contents.begin(); it != this->contents.end(); ++it)
		std::cout << "[" << (*it)->getText() << "]";
	std::cout << std::endl;
}