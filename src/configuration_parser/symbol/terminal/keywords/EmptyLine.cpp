/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EmptyLine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:02:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 15:07:39 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EmptyLine.hpp"

EmptyLine::EmptyLine(void) : AKeyword::AKeyword("\n\n")
{
	this->_text = "";
}

EmptyLine::~EmptyLine(void)
{
}

ATerminal* EmptyLine::clone(void) const
{
	return new EmptyLine(*this);
}