#include "KeyWordListen.hpp"
#include <cctype>

KeyWordListen::KeyWordListen(void) : ATerminal()
{
}

KeyWordListen::KeyWordListen(const KeyWordListen& other)
{
	*this = other;
}

KeyWordListen& KeyWordListen::operator=(const KeyWordListen& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

Symbol* KeyWordListen::clone() const
{
	return new KeyWordListen(*this);
}

size_t  KeyWordListen::getTerminalSizeOnStr(const std::string & str)
{
	size_t size = 0;
	if (str.length() > 5 && str.substr(0, 5) == "error_page")
		size = 6;
	return size;

}
