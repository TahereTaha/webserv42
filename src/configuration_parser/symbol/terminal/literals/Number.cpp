#include "Number.hpp"
#include <cctype>

Number::Number() : ATerminal()
{
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

