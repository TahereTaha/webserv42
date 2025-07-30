/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Schemas.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:02:42 by capapes           #+#    #+#             */
/*   Updated: 2025/07/28 15:05:03 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include <vector>
#include "Request.hpp"
#include "Headers.hpp"
#include "ControlData.hpp"
#include "FieldValidators.hpp"


// =====================================================================
// 	DELIMITERS DEFINITIONS
// =====================================================================
#define EOL				"\0"
#define SP				" "
#define TB				"\t"
#define END_OF_HEADERS 	"\r\n\r\n"
#define END_OF_LINE 	"\r\n"

// =====================================================================
// 	SCHEMA DEFINITIONS
// =====================================================================
struct SchemaItem {
    const char* 	delimiter;
    bool 			(*fn)(const std::string&);
    const char* 	error;
    int 			errorCode;
    bool 			isRequired;
};

Request validateRequest(const std::string& raw);