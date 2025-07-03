/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrMatchUtils.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:23:20 by capapes           #+#    #+#             */
/*   Updated: 2025/07/03 12:35:34 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

std::string getFirstOcurrence(const std::string& str, const std::string& toFind, bool isCaseSensitive = true);
std::string strIter(std::string str, int (*func)(int));
std::string toUpper(std::string str);
std::string toLower(std::string str);