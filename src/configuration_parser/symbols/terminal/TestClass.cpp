/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestClass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:27:45 by capapes           #+#    #+#             */
/*   Updated: 2025/07/01 18:12:47 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestClass.hpp"
#include <cstring>



TestPattern::TestPattern()
{
}

TestPattern::TestPattern(const std::string &src)
{
	_text = get_pattern(src, "test");
}

Terminal* TestPattern::clone(const std::string &str) const
{
	return (new TestPattern(str));
}
