/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AKeyword.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:40:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/20 17:53:43 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <ATerminal.hpp>
#include <StrMatchUtils.hpp>

class AKeyWord : public ATerminal
{
	private:
		AKeyword();
	protected:
		std::string	_keyword;
		AKeyword(const std::string & src);
	public:
		~AKeyword(void);

		virtual size_t		getTerminalSizeOnStr(const std::string & str) const override; // careful, override is C++11
		virtual ATerminal* 	clone(void) const = 0;
};
