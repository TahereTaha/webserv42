/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerminalFactoryTest.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:00:21 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 18:16:59 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "TerminalFactory.hpp"
#include "TestClass.hpp"
#include "NumberToken.hpp"

class TerminalFactoryTest : public TerminalFactory
{
	private:
	protected:
	public:
		TerminalFactoryTest(std::string content);
		virtual ~TerminalFactoryTest();
};


TerminalFactoryTest::TerminalFactoryTest(std::string content)
	: TerminalFactory(content)
{
	_constructors.push_back(new TestPattern());
	_constructors.push_back(new NumberToken());
}