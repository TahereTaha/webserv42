/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AKeyword.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:22:10 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 15:01:27 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AKeyword.hpp"

AKeyword::AKeyword(const std::string & str) : ATerminal()
{
	_keyword = str;
}

AKeyword::~AKeyword(void){}

size_t		AKeyword::getTerminalSizeOnStr(const std::string & str) const
{
	return startsWith(str, _keyword) ? _keyword.length() : 0;
}