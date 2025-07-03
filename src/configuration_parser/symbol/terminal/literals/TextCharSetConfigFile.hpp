/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextCharSetConfigFile.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:23:03 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 13:10:22 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../TerminalFactory.hpp"
#include "AlphaToken.hpp"
#include "TextCharSetConfigFileToken.hpp"

class AlphaNumericalToken : public Terminal
{
	private:
	protected:
	public:
		TextCharSetConfigFile(void);
		TextCharSetConfigFile(const TextCharSetConfigFile & src);
		TextCharSetConfigFile & operator = (const TextCharSetConfigFile & src);
		TextCharSetConfigFile(void);

		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;
};

