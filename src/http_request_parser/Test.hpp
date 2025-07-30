/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:09:11 by capapes           #+#    #+#             */
/*   Updated: 2025/07/28 15:02:42 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "Request.hpp"
#include "Headers.hpp"
#include "ControlData.hpp"
#include "Schemas.hpp"


struct TestCase {
    std::string raw;
    Request expected;

    TestCase(const std::string &r, const Request &req)
        : raw(r), expected(req) {}
};
