/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:24:29 by capapes           #+#    #+#             */
/*   Updated: 2025/07/07 11:16:22 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <HTTP.hpp>

HTTP::HTTP(void) : AKeyWord::AKeyWord("HTTP")
{
	this->_text = "";
}

HTTP::~HTTP(void)
{
}

ATerminal* HTTP::clone(void) const
{
	return new HTTP(*this);
}
