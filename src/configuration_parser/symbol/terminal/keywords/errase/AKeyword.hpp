/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AKeyword.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:40:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 12:42:08 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <stddef.h>

class AKeyword : public ATerminal
{
	private:
	protected:
	public:
		AKeyword(void);
		virtual ~AKeyword(void);

		virtual size_t getTerminalSizeOnStr(const std::string & str) const = 0;
		virtual ATerminal* clone(void) const = 0;
};