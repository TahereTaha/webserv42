/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:31:18 by capapes           #+#    #+#             */
/*   Updated: 2025/07/07 11:17:41 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ATerminal.hpp>

class Block : public ATerminal
{
	private:
	protected:
	public:
		Block(void);
		~Block(void) {}

		virtual ATerminal* clone(void) const override
		{
			return new Block(*this);
		}

		size_t getTerminalSizeOnStr(const std::string & str) const
};
