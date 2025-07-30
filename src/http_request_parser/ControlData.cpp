/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:54:25 by capapes           #+#    #+#             */
/*   Updated: 2025/07/28 16:31:55 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ControlData.hpp"

bool ControlData::operator==(const ControlData &other) const {
    return method == other.method &&
           requestTarget == other.requestTarget &&
           httpVersion == other.httpVersion;
}