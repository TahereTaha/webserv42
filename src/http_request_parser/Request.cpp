/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:20:26 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 20:31:11 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <stdio.h>
#include <iostream>
#include "ControlData.hpp"

Request::Request()
    : controlData(), headers(), body(""), errorCode(0) {
 
    }

Request::Request(const ControlData& cd, const Headers& h, const std::string& b)
    : controlData(cd), headers(h), body(b), errorCode(0) {
            Request::setActiveRequest(this);
            Request::setActiveError(0);
    }

Request::Request(const Request& other)
    : controlData(other.controlData),
      headers(other.headers),
      body(other.body),
      errorCode(other.errorCode) {}

Request& Request::operator=(const Request& other) {
    if (this != &other) {
        controlData = other.controlData;
        headers = other.headers;
        body = other.body;
        errorCode = other.errorCode;
    }
    return *this;
}

// bool Request::operator==(const Request& other) const {
//     return controlData == other.controlData &&
//            headers == other.headers &&
//            body == other.body &&
//            errorCode == other.errorCode;
// }

Request::~Request() {}


void Request::setControlData(const ControlData& cd) {
    controlData = cd;
}

void Request::setHeaders(const Headers& h) {
    headers = h;
}

void Request::setBody(const std::string& b) {
    body = b;
}

void Request::setErrorCode(int code) {
    errorCode = code;
}

const ControlData& Request::getControlData() const {
    return controlData;
}

const Headers& Request::getHeaders() const {
    return headers;
}

const std::string& Request::getBody() const {
    return body;
}

int Request::getErrorCode() const {
    return errorCode;
}

Request* Request::activeRequest = NULL;

void Request::setActiveRequest(Request* r) {
	activeRequest = r;
}

void Request::setActiveError(int code) {
	if (activeRequest)
		activeRequest->setErrorCode(code);
}

