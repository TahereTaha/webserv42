/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlphaTopken.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:18:44 by capapes           #+#    #+#             */
/*   Updated: 2025/07/02 02:19:23 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Terminal.hpp"

class AlphaToken : public Terminal
{
	private:
	protected:
	public:
		AlphaToken(void);
		Terminal* clone() const;
		void setText(const std::string &text);
};