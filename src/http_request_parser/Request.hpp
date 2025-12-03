/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:17:20 by capapes           #+#    #+#             */
/*   Updated: 2025/12/01 18:57:51 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include "ControlData.hpp"
#include "Headers.hpp"

class Request {
public:
    Request();
    Request(const ControlData& cd, const Headers& h, const std::string& b);
    Request(const Request& other);
    Request& operator=(const Request& other);
    ~Request();

    // bool             operator==(const Request& other) const;
    void 				setControlData(const ControlData& cd);
    void 				setHeaders(const Headers& h);
    void 				setBody(const std::string& b);

    const ControlData& 	getControlData() 	const;
    const Headers& 		getHeaders() 		const;
    const std::string& 	getBody() 			const;
    int 				getErrorCode() 		const;
	static void 		setActiveRequest(Request* r);
    static void 		setActiveError(int code);
    static Request* 	getActiveRequest();
    static int 		    getActiveError();
    void                setErrorCode(int code);
private:
    ControlData 		controlData;
    Headers 			headers;
    std::string 		body;
    int 				errorCode;

	static Request* 	activeRequest;
};
