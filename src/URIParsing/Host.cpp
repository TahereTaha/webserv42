#include <Host.hpp>

#include <vector>
#include <string>

//	helper functions.

static std::string	consume_IP_LITERAL(std::vector<std::string>::iterator &iter, \
		std::vector<std::string>::iterator end)
{
	std::string	text = "";

	if (iter != end)
	{
		text += *iter;
		iter++;
	}
	while (iter != end && *iter != "]")
	{
		text += *iter;
		iter++;
	}
	if (iter != end)
	{
		text += *iter;
		iter++;
	}
	return (text);
}

static std::string	consume_REG_NAME(std::vector<std::string>::iterator &iter, \
		std::vector<std::string>::iterator end)
{
	std::string	text = "";
	if (iter != end)
	{
		text += *iter;
		iter++;
	}
	return (text);
}

//	class methods.

Host::Host(void)
{
}

Host::Host(std::string text)
{
	this->_text = text;
	this->identifyHostType();
}

//	the logic for identifing the host type is duplicated 
//	here too, for consuming only  the nesesary tokens
Host::Host(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end)
{
	this->_text = "";
	if  (*iter == "[")
		this->_text = consume_IP_LITERAL(iter, end);
	else
		this->_text = consume_REG_NAME(iter, end);
	this->identifyHostType();
}

Host::~Host(void)
{
}

void	Host::identifyHostType(void)
{
}

