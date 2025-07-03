#include "KeyWordReturn.hpp"
#include <cctype>

KeyWordReturn::KeyWordReturn(void)
{
	this->_text = "";
}

KeyWordReturn::KeyWordReturn(const KeyWordReturn& other)
{
	*this = other;
}

KeyWordReturn& KeyWordReturn::operator=(const KeyWordReturn& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

Symbol* KeyWordReturn::clone() const
{
	return new KeyWordReturn(*this);
}

size_t  KeyWordReturn::getTerminalSizeOnStr(const std::string & str)
{
	size_t size = 0;
	if (str.length() > 5 && str.substr(0, 5) == "return")
		size = 6;
	return size;
}

