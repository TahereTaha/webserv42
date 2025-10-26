#pragma once

#include <vector>
#include <string>

typedef enum
{
	REG_NAME = 0 ,					//	REG_NAME is registered name.
	IP_LITERAL,
}	t_host_type;

class Host
{
	private:
		std::string	_text;

		t_host_type	_type;

//		IP_LITERAL	_ip;

	protected:
	public:
		Host(void);
		Host(std::string text);
		Host(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end);
		~Host(void);
};

