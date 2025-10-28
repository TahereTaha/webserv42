#pragma once

#include <string>
#include <stdint.h>

#define IP_V4_DATA_SIZE 4
#define IP_V6_DATA_SIZE 16

#define IP_MAX_DATA_SIZE IP_V6_DATA_SIZE	//	enough to store a ipv6

typedef enum
{
	IP_V_4 = 0,
	IP_V_6,
	IP_V_FUTURE,
}	t_IpLiteral_type;

class IpLiteral
{
	private:
		std::string	_text;

		t_IpLiteral_type	_type;
		uint8_t	_data[IP_MAX_DATA_SIZE];

		void	identifyType(void);
	protected:
	public:
		IpLiteral(void);
		IpLiteral(std::string text);
		~IpLiteral(void);

		t_IpLiteral_type	getType(void) const;
		uint8_t				*getData(void);

		//	this is for debug purposes only.
		void	print(void) const;
};

