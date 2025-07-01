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

TestFactory::TestFactory()
{
}

TestFactory::TestFactory(const std::string &src)
{
	_text = get_pattern(src, "test");
}

Terminal* TestFactory::clone(const std::string &str) const
{
	return (new TestFactory(str));
}
