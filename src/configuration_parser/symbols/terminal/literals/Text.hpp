/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlphaNumericalToken.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:23:03 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 02:23:09 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../TerminalFactory.hpp"
#include "AlphaToken.hpp"
#include "NumberToken.hpp"

class AlphaNumericalToken : public Terminal
{
	private:
	protected:
	public:
		AlphaNumericalToken(void);
		Terminal* clone() const;
		void setText(const std::string &text);
};