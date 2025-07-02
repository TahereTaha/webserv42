#include "Number.hpp"
#include <cctype>

Number::Number(void)
{
	this->_text = "";
}

Number::Number(std::string str)
{
	setText(str);
}

Number::Number(const Number& other)
{
	*this = other;
}

Number& Number::operator=(const Number& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

Symbol* Number::clone() const
{
	return new Number(*this);
}

void Number::setText(const std::string& str)
{
	int i = 0;

	std::string::const_iterator it = str.begin();
	
	while (it != str.end() && isdigit(*it))
	{
		i++;
		it++;
	}
	this->_text = str.substr(0, i);
}
