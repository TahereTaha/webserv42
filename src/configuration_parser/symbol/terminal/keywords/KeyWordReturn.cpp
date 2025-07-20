#include "KeyWordReturn.hpp"
#include <cctype>

KeyWordReturn::KeyWordReturn(void) : ATerminal()
{
}

ASymbol* KeyWordReturn::clone() const
{
	return new KeyWordReturn(*this);
}

size_t  KeyWordReturn::getTerminalSizeOnStr(const std::string & str) const 
{
	size_t size = 0;
	if (str.length() > 5 && str.substr(0, 5) == "return")
		size = 6;
	return size;
}

