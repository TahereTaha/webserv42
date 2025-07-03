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

size_t	Number::getTerminalSizeOnStr(const std::string & str)
{
	size_t					size = 0;
	std::string::iterator	it = str.begin();

	while (it != str.end() && isdigit(*it))
	{
		size++;
		it++;
	}
	return (size);
}
