/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:36:50 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 19:53:18 by capapes          ###   ########.fr       */
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

    ControlData()
        : method(""), requestTarget(""), httpVersion("") {}
    ControlData(const std::string &m, const std::string &rt, const std::string &hv)
        : method(m), requestTarget(rt), httpVersion(hv) {}
};

