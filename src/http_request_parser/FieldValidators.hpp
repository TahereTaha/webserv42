/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:15:06 by capapes           #+#    #+#             */
/*   Updated: 2025/07/17 15:16:09 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <string>

void isValidFieldName(const std::string& fieldName);
void isValidfieldValue(const std::string& fieldValue);
void isValidMethod(const std::string& method, int &statusCode);
void isValidProtocolVersion(const std::string& version, int &statusCode);
void isValidRequestTarget(const std::string& target, int &statusCode);
