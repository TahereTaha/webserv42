#include "KeyWordErrorPage.hpp"
#include <cctype>

KeyWordErrorPage::KeyWordErrorPage(void) : ATerminal()
{
}

KeyWordErrorPage::KeyWordErrorPage(const KeyWordErrorPage& other)
{
	*this = other;
}

KeyWordErrorPage& KeyWordErrorPage::operator=(const KeyWordErrorPage& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

Symbol* KeyWordErrorPage::clone() const
{
	return new KeyWordErrorPage(*this);
}

size_t	getTerminalSizeOnStr(const std::string & str)
{
	size_t size = 0;
	if (str.length() > 9 && str.substr(0, 9) == "error_page")
		size = 10;
	return size;
}
