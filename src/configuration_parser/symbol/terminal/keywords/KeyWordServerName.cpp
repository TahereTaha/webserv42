#include "KeyWordServerName.hpp"
#include <cctype>

KeyWordServerName::KeyWordServerName(void) : AKeyWord("server_name")
{
}

KeyWordServerName::~KeyWordServerName(void)
{
}

ASymbol* KeyWordServerName::clone() const
{
	return new KeyWordServerName(*this);
}

