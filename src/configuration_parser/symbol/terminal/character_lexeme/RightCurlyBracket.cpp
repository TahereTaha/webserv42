#include "RightCurlyBracket.hpp"

RightCurlyBracket::RightCurlyBracket(void)
{
	this->_text = "";
}

RightCurlyBracket::RightCurlyBracket(std::string str)
{
	setText(str);
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

Symbol* RightCurlyBracket::clone() const
{
	return new RightCurlyBracket(*this);
}

void RightCurlyBracket::setText(const std::string& str)
{
	if (!str.empty() && str[0] == '}')
		this->_text = "}";
	else
		this->_text = "";
}
