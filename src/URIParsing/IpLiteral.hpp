#pragma once

#include <string>

class IpLiteral
{
	private:
		std::string	_text;
	protected:
	public:
		IpLiteral(void);
		IpLiteral(std::string text);
		~IpLiteral(void);
};
