#include "KeyWordListen.hpp"
#include <cctype>

KeyWordListen::KeyWordListen(void) : ATerminal()
{
}

ASymbol* KeyWordListen::clone() const
{
	return new KeyWordListen(*this);
}

size_t  KeyWordListen::getTerminalSizeOnStr(const std::string & str) const 
{
	size_t size = 0;
	if (str.length() > 5 && str.substr(0, 5) == "listen")
		size = 6;
	return size;

}
