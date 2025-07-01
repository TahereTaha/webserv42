/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NotDefinedSymbol.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:46:08 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 17:46:15 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Terminal.hpp>
class NotDefinedSymbol : public Terminal
{
	private:
	protected:
	public:
		NotDefinedSymbol(void);
		NotDefinedSymbol(std::string str);
		virtual Terminal* clone(const std::string &str) const;
};