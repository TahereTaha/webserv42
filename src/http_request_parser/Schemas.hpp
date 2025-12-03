/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Schemas.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:02:42 by capapes           #+#    #+#             */
/*   Updated: 2025/12/03 18:01:04 by capapes          ###   ########.fr       */
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
// 	Conditional Schemas flags
// =====================================================================
enum SchemaFlags {    
    NONE            = 0,
    LEADING         = 1 << 0,
    TRAILING        = 1 << 1,  
    OPTIONAL_SPACES = (LEADING | TRAILING),
    IS_REQUIRED     = 1 << 2,
};

// =====================================================================
// 	DELIMITERS DEFINITIONS
// =====================================================================
#define EOF_			"\0"
#define SP				" "
#define TB				"\t"
#define END_OF_HEADERS 	"\r\n\r\n"
#define END_OF_LINE 	"\r\n"
#define NEW_LINE        "\n"
#define EMPTY_STRING    ""
#define SPACES          " \t\n\r\f\v"

// =====================================================================
// 	SCHEMA DEFINITIONS
// =====================================================================
struct SchemaItem {
    const char* 	delimiter;
    bool 			(*fn)(const std::string&);
    const char* 	error;
    int 			errorCode;
    int             flags; // Flags for optional spaces, allow empty, etc.
};

Request validateRequest(const std::string& raw);
