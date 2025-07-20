#include "KeyWordServerName.hpp"
#include <cctype>

KeyWordServerName::KeyWordServerName(void) : ATerminal()
{
}


ASymbol* KeyWordServerName::clone() const
{
	return new KeyWordServerName(*this);
}

size_t  KeyWordServerName::getTerminalSizeOnStr(const std::string & str) const 
{
	size_t size = 0;
	if (str.length() >  10 && str.substr(0, 10) == "server_name")
		size = 11;
	return size;
}
