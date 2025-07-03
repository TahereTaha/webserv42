/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:24:29 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 12:39:41 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ErrorPage.hpp>

ErrorPage::ErrorPage(void)
{
	this->_text = "";
}

ErrorPage::ErrorPage(std::string str)
{
	_text = getFirstOcurrence(str, "error_page");
}

size_t ErrorPage::getTerminalSizeOnStr(const std::string & str) const
{
	return getFirstOcurrence(str, "error_page").length();
}