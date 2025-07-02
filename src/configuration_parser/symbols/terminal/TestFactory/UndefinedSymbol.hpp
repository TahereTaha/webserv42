/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UndefinedSymbol.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:46:08 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 18:53:59 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Terminal.hpp"
class UndefinedSymbol : public Terminal
{
	private:
	protected:
	public:
		UndefinedSymbol(void);
		Terminal* clone() const;
		void setText(const std::string &text);
};