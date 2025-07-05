/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AKeyword.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:40:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 15:00:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <ATerminal.hpp>
#include <StrMatchUtils.hpp>

class AKeyword : public ATerminal
{
	private:
		AKeyword();
	protected:
		std::string	_keyword;
	public:
		AKeyword(const std::string & src);
		~AKeyword(void);

		virtual size_t		getTerminalSizeOnStr(const std::string & str) const override; // careful, override is C++11
		virtual ATerminal* 	clone(void) const = 0;
};
