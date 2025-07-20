/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:47:49 by capapes           #+#    #+#             */
/*   Updated: 2025/07/20 18:08:04 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

// Function to extract a field from the request line based on the given delimiter
std::string getField(size_t& pos, const std::string& src, const std::string& delimiter);
