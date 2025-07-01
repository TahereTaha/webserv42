/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UndefinedSymbol.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:46:34 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 17:46:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UndefinedSymbol.hpp"

UndefinedSymbol::UndefinedSymbol(void)
{
	_text = "";
}
Terminal* UndefinedSymbol::clone() const
{
	return (new UndefinedSymbol(*this));
}

void UndefinedSymbol::setText(const std::string &text)
{
	_text = "";
	if (text.empty())
		return;
}