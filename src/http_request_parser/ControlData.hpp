/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:36:50 by capapes           #+#    #+#             */
/*   Updated: 2025/12/01 15:17:25 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// Module pattern
// Schema (table) → ExtractAndValidate() → Strategy Validator 

#pragma once
#include <string>

struct ControlData {
    std::string method;
    std::string requestTarget;
    std::string httpVersion;
    size_t      size;

    ControlData()
        : method(""), requestTarget(""), httpVersion(""), size(0) {}
    ControlData(const std::string &m, const std::string &rt, const std::string &hv, size_t s)
        : method(m), requestTarget(rt), httpVersion(hv), size(s) {}
};

