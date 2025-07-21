#include "KeyWordErrorPage.hpp"
#include <cctype>

KeyWordErrorPage::KeyWordErrorPage(void) : AKeyWord("error_page")
{
}

KeyWordErrorPage::~KeyWordErrorPage(void)
{
}

ASymbol* KeyWordErrorPage::clone() const
{
	return new KeyWordErrorPage(*this);
}
