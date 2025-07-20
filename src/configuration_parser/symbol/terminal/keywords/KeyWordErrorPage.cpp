#include "KeyWordErrorPage.hpp"
#include <cctype>

KeyWordErrorPage::KeyWordErrorPage(void) : ATerminal()
{
}

ASymbol* KeyWordErrorPage::clone() const
{
	return new KeyWordErrorPage(*this);
}

size_t	KeyWordErrorPage::getTerminalSizeOnStr(const std::string & str) const
{
	size_t size = 0;
	if (str.length() > 9 && str.substr(0, 9) == "error_page")
		size = 10;
	return size;
}
