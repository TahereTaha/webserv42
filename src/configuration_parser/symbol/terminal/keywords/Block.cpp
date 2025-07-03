/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:02:11 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 15:50:14 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Block.hpp"

Block::Block(void) : ATerminal()
{
	this->_text = "";
}

Block::~Block(void)
{
}

size_t Block::getTerminalSizeOnStr(const std::string & str) const
{
	size_t pos = str.find("\n\n");
	pos = (pos == std::string::npos) ? str.find("\r\n\r\n") : pos;
	return (pos != std::string::npos) ? pos + 2 : 0;
}
