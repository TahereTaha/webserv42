#include "KeyWordListen.hpp"
#include <cctype>

KeyWordListen::KeyWordListen(void) : AKeyWord("listen")
{
}

KeyWordListen::~KeyWordListen(void)
{
}
	
ATerminal* KeyWordListen::clone() const
{
	return new KeyWordListen(*this);
}
