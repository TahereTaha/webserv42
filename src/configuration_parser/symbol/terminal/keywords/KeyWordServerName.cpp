#include "KeyWordServerName.hpp"
#include <cctype>

KeyWordServerName::KeyWordServerName(void) : ATerminal()
{
}

KeyWordServerName::KeyWordServerName(const KeyWordServerName& other)
{
	*this = other;
}

KeyWordServerName& KeyWordServerName::operator=(const KeyWordServerName& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

Symbol* KeyWordServerName::clone() const
{
	return new KeyWordServerName(*this);
}

size_t  KeyWordKeyWordServerName::getTerminalSizeOnStr(const std::string & str)
{
	size_t size = 0;
	if (str.length() >  10 && str.substr(0, 10) == "server_name")
		size = 11;
	return size;
}
