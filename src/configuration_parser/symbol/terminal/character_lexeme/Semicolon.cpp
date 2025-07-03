#include "Semicolon.hpp"

Semicolon::Semicolon(void)
{
	this->_text = "";
}

Semicolon::Semicolon(std::string str)
{
	setText(str);
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

Symbol* Semicolon::clone() const
{
	return new Semicolon(*this);
}

void Semicolon::setText(const std::string& str)
{
	if (!str.empty() && str[0] == ';')
		this->_text = ";";
	else
		this->_text = "";
}
