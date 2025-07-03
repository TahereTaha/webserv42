#include "ServerName.hpp"
#include <cctype>

ServerName::ServerName(void)
{
	this->_text = "";
}

ServerName::ServerName(std::string str)
{
	
	if (str.length() > 10 && str.substr(0, 10) == "server_name")
		this->_text = str.substr(0, 10);
	else
		this->_text = "";
}

ServerName::ServerName(const ServerName& other)
{
	*this = other;
}

ServerName& ServerName::operator=(const ServerName& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

