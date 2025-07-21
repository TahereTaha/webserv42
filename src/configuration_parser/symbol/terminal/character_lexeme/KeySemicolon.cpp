#include <KeySemicolon.hpp>

KeySemicolon::KeySemicolon(void) : AKeyWord(";")
{
}

KeySemicolon::~KeySemicolon(void)
{
}

ATerminal* KeySemicolon::clone(void) const
{
	return (new KeySemicolon(*this));
}
