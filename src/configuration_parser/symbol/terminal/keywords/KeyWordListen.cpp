#include "KeyWordListen.hpp"
#include <cctype>

KeyWordListen::KeyWordListen(void) : AKeyWord("listen")
{
}

KeyWordListen::~KeyWordListen(void)
{
}
	
ASymbol* KeyWordListen::clone() const
{
	return new KeyWordListen(*this);
}
