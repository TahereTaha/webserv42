/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldValidators.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/configuration_parser/symbol/terminal/keywords/EmptyLine.hpp
/*   Created: 2025/07/03 15:03:18 by capapes           #+#    #+#             */
/*   Updated: 2025/07/07 11:18:10 by tatahere         ###   ########.fr       */
=======
/*   Created: 2025/07/17 15:15:06 by capapes           #+#    #+#             */
/*   Updated: 2025/07/17 15:16:09 by capapes          ###   ########.fr       */
>>>>>>> 4cd62cef78235571a76907447f80add319ab5904:src/http_request_parser/FieldValidators.hpp
/*                                                                            */
/* ************************************************************************** */

#pragma once

<<<<<<< HEAD:src/configuration_parser/symbol/terminal/keywords/EmptyLine.hpp
#include <AKeyWord.hpp>

class EmptyLine : public AKeyWord
{
	private:
	protected:
	public:
		EmptyLine(void);
		~EmptyLine(void) {}

		virtual ATerminal* clone(void) const override
		{
			return new EmptyLine(*this);
		}
};
=======
#include <stdexcept>
#include <string>

void isValidFieldName(const std::string& fieldName);
void isValidfieldValue(const std::string& fieldValue);
void isValidMethod(const std::string& method, int &statusCode);
void isValidProtocolVersion(const std::string& version, int &statusCode);
void isValidRequestTarget(const std::string& target, int &statusCode);
>>>>>>> 4cd62cef78235571a76907447f80add319ab5904:src/http_request_parser/FieldValidators.hpp
