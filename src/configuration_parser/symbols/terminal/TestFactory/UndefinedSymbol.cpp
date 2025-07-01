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
	_text = "Not Defined";
}
UndefinedSymbol::UndefinedSymbol(std::string str)
{
	_text = str;
}
Terminal* UndefinedSymbol::clone(const std::string &str) const
{
	return (new UndefinedSymbol(str));
}