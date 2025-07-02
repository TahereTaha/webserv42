#include "RightCurlyBracket.hpp"

RightCurlyBracket::RightCurlyBracket(void)
{
	this->_text = "";
}

RightCurlyBracket::RightCurlyBracket(std::string str)
{
	if (!str.empty() && str[0] == '}')
		this->_text = "}";
	else
		this->_text = "";
}

RightCurlyBracket::RightCurlyBracket(const RightCurlyBracket& other)
{
	*this = other;
}

RightCurlyBracket& RightCurlyBracket::operator=(const RightCurlyBracket& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}
