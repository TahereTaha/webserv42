/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTerminalVector.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 01:29:21 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 01:35:33 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TypeTerminalVector.hpp"

TerminalVector::TerminalVector() {
	match = nullptr;
}

TerminalVector::~TerminalVector()
{
	for (TerminalVector::iterator it = this->begin(); it != this->end(); ++it)
		delete *it;
}

void TerminalVector::setAll(std::string content)
{
	int longestLength = 0;
	match = nullptr;
	for (TerminalVector::iterator it = this->begin(); it != this->end(); ++it)
	{
		(*it)->setText(content);
		if ((*it)->length() > longestLength)
		{
			longestLength = (*it)->length();
			match = *it;
		}
	}
}