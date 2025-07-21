#include "KeyWordReturn.hpp"
#include <cctype>

KeyWordReturn::KeyWordReturn(void) :AKeyWord("return")
{
}

KeyWordReturn::~KeyWordReturn(void)
{
}

ASymbol* KeyWordReturn::clone() const
{
	return new KeyWordReturn(*this);
}
