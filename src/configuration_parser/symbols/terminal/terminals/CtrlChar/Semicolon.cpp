#include "Semicolon.hpp"

Semicolon::Semicolon(void)
{
	this->_text = "";
}

Semicolon::Semicolon(std::string str)
{
	if (!str.empty() && str[0] == ';')
		this->_text = ";";
	else
		this->_text = "";
}

Semicolon::Semicolon(const Semicolon& other)
{
	*this = other;
}

Semicolon& Semicolon::operator=(const Semicolon& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}
