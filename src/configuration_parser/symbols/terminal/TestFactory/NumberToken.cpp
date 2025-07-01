/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberToken.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:08:00 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 19:08:10 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NumberToken.hpp"

NumberToken::NumberToken(void)
{
	_text = "";
}

NumberToken::NumberToken(std::string str)
{
	_text = get_pattern(str, "0123456789");
}