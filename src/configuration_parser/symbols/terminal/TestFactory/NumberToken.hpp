/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberToken.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:10:09 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 19:26:38 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Terminal.hpp"

class NumberToken : public Terminal
{
	private:
	protected:
	public:
		NumberToken(void);
		NumberToken(std::string str);
		virtual Terminal* clone(const std::string &str) const;
};

