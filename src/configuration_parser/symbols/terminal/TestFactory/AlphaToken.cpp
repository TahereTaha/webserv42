/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlphaToken.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:18:56 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 02:19:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AlphaToken.hpp"

AlphaToken::AlphaToken(void)
{
	_text = "";
}

Terminal* AlphaToken::clone() const
{
	return new AlphaToken(*this);
}

void AlphaToken::setText(const std::string &text)
{
	_text = get_pattern(text, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}
