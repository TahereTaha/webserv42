/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberToken.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:08:00 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 22:09:57 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NumberToken.hpp"

NumberToken::NumberToken(void)
{
	_text = "";
}

Terminal* NumberToken::clone() const
{
	return new NumberToken(*this);
}

void NumberToken::setText(const std::string &text)
{
	_text = get_pattern(text, "0123456789");
}