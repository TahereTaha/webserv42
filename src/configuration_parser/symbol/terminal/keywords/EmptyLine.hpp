/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EmptyLine.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:03:18 by capapes           #+#    #+#             */
/*   Updated: 2025/07/07 11:18:10 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <AKeyWord.hpp>

class EmptyLine : public AKeyWord
{
	private:
	protected:
	public:
		EmptyLine(void);
		~EmptyLine(void) {}

		virtual ATerminal* clone(void) const override
		{
			return new EmptyLine(*this);
		}
};
