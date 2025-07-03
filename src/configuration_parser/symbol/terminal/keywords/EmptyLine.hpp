/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EmptyLine.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:03:18 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 15:06:47 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <AKeyword.hpp>

class EmptyLine : public AKeyword
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