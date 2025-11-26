/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:35:10 by capapes           #+#    #+#             */
/*   Updated: 2025/10/07 14:17:48 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <iostream>
#include <cerrno>


// enum ErrorType {
//     EPOLL_CTL_FAILED = 500,
	
// };

// std::string getErrorMesage(ErrorType type) {
//     std::string typeStr;

//     switch (type) {
//         case EPOLL_CTL_FAILED:       typeStr = "[ERROR] Error setting epoll instance for fd "; break;
//     }
//     return typeStr;
// }

// void exitWithError(ErrorType errorCode) {
// 	std::string errorMessage;
	
// 	// errorMessage = getErrorMesage(errorCode);
// 	// perror(errorMessage.c_str());
// 	exit(EXIT_FAILURE);
// }