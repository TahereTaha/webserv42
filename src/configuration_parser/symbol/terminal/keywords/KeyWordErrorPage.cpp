#include "KeyWordErrorPage.hpp"
#include <cctype>

KeyWordErrorPage::KeyWordErrorPage(void) : AKeyWord("error_page")
{
}

KeyWordErrorPage::~KeyWordErrorPage(void)
{
}

ATerminal* KeyWordErrorPage::clone() const
{
	return new KeyWordErrorPage(*this);
}

const char	*KeyWordErrorPage::what(void) const 
{
	return ("error_page");
}
