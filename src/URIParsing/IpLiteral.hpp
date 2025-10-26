#pragma once

#include <string>
#include <stdint.h>

#define IP_MAX_DATA_SIZE 16

typedef enum
{
	IP_V_4;
	IP_V_6;
	IP_V_FUTURE;
}	t_IpLiteral_type;

class IpLiteral
{
	private:
		std::string	_text;

		t_IpLiteral_type	_type;

		uint8_t	data[IP_MAX_DATA_SIZE];
	protected:
	public:
		IpLiteral(void);
		IpLiteral(std::string text);
		~IpLiteral(void);
};
