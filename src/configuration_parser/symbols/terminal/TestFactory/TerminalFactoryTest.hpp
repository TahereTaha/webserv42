/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalFactoryTest.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:00:21 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 19:32:27 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../TerminalFactory.hpp"


class TerminalFactoryTest : public TerminalFactory
{
	private:
	protected:
	public:
		TerminalFactoryTest(std::string content);
		~TerminalFactoryTest();
};

