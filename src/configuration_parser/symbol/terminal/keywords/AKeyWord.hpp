/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AKeyWord.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:40:41 by capapes           #+#    #+#             */
/*   Updated: 2025/07/07 11:13:40 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ATerminal.hpp>

class AKeyWord : public ATerminal
{
	private:
		AKeyWord();

	protected:
		const std::string	_keyWord;
	public:
		AKeyWord(const std::string & src);
		size_t		getTerminalSizeOnStr(const std::string & str) const;
};

bool	startsWith(const std::string& str, const std::string& toFind, bool caseSensitive = true);

std::string	strIter(std::string str, int (*func)(int));
std::string toUpper(std::string str);
std::string toLower(std::string str);
