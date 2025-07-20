/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EmptyLine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:02:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/07 11:25:52 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EmptyLine.hpp"

EmptyLine::EmptyLine(void) : AKeyWord::AKeyWord("\n\n")
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
