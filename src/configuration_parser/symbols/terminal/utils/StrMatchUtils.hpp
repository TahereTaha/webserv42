/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrMatchUtils.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:23:20 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 14:36:15 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

bool 		startsWith(const std::string& str, const std::string& toFind, bool caseSensitive = true);
std::string strIter(std::string str, int (*func)(int));
std::string toUpper(std::string str);
std::string toLower(std::string str);