/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberToken.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:10:09 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 22:11:55 by capapes          ###   ########.fr       */
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
		Terminal* clone() const;
		void setText(const std::string &text);
};

