/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlphaNumericalToken.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:22:46 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 16:09:45 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AlphaNumericalToken.hpp"

AlphaNumericalToken::AlphaNumericalToken(void)
{
	_text = "";
}


Terminal* AlphaNumericalToken::clone() const
{
	return new AlphaNumericalToken(*this);
}

void AlphaNumericalToken::setText(const std::string &text)
{
	std::string alpha = get_pattern(text, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	std::string number = get_pattern(text.substr(alpha.length()), "0123456789");
	_text = alpha + number;
}