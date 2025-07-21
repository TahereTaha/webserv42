#include <KeySemicolon.hpp>

KeySemicolon::KeySemicolon(void) : AKeyWord(";")
{
}

KeySemicolon::~KeySemicolon(void)
{
}

ASymbol* KeySemicolon::clone(void) const
{
	return (new KeySemicolon(*this));
}
