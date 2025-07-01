/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestFactory.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:27:45 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 18:12:47 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestFactory.hpp"

TestFactory::TestFactory() {}

TestFactory::TestFactory(std::string src)
{
	_text = get_pattern(src, "test");
}

Terminal* TestFactory::clone() const
{
	return (new TestFactory(_text));
}

void TestFactory::setText(const std::string &text)
{
	_text = get_pattern(text, "test");
}

TestFactory::~TestFactory()
{
}
