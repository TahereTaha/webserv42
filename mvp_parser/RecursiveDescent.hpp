/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RecursiveDescent.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:23:07 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 19:24:00 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "TerminalFactory.hpp"

class RecursiveDescent : public TerminalFactory
{
	private:
		RecursiveDescent(const RecursiveDescent &src);
	protected:
		std::vector<std::string> _tokens;
		int _currentIndex;
		void parseExpression();
		void parseTerm();
		void parseFactor();
	public:
		RecursiveDescent(std::string content);
		virtual	~RecursiveDescent();
		void	parse();
};