#include "KeyWordServerName.hpp"
#include <cctype>

KeyWordServerName::KeyWordServerName(void) : AKeyWord("server_name")
{
}

KeyWordServerName::~KeyWordServerName(void)
{
}

ATerminal* KeyWordServerName::clone() const
{
	return new KeyWordServerName(*this);
}

const char	*KeyWordServerName::what(void) const 
{
	return ("server_name");
}
