/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NotDefinedSymbol.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:46:34 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 17:46:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NotDefinedSymbol.hpp"

NotDefinedSymbol::NotDefinedSymbol(void)
{
	_text = "Not Defined";
}
NotDefinedSymbol::NotDefinedSymbol(std::string str)
{
	_text = str;
}
Terminal* NotDefinedSymbol::clone(const std::string &str) const
{
	return (new NotDefinedSymbol(str));
}