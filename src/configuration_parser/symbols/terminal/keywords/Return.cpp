#include "Return.hpp"
#include <cctype>

Return::Return(void)
{
	this->_text = "";
}

Return::Return(std::string str)
{
	
	if (str.length() > 5 && str.substr(0, 5) == "return")
		this->_text = str.substr(0, 5);
	else
		this->_text = "";
}

Return::Return(const Return& other)
{
	*this = other;
}

Return& Return::operator=(const Return& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

