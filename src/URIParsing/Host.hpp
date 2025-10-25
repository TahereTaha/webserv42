#pragma once

#include <vector>
#include <string>

typedef enum
{
	REG_NAME = 0 ,					//	REG_NAME is registered name.
	IP_V4_ADDRESS,
	IP_LITERAL,
	IP_LITERAL_V6_ADDRESS,
	IP_LITERAL_V_FUTURE,
	IP_LITERAL_UNSUPORTED,
}	t_host_type;

class Host
{
	private:
		std::string	_text;

		t_host_type	_type;

		void	identifyHostType(void);
	protected:
	public:
		Host(void);
		Host(std::string text);
		Host(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end);
		~Host(void);
};

