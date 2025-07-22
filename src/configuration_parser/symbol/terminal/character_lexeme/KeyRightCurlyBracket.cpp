#include <KeyRightCurlyBracket.hpp>

KeyRightCurlyBracket::KeyRightCurlyBracket(void) : AKeyWord("}")
{
}

KeyRightCurlyBracket::~KeyRightCurlyBracket(void)
{
}

ATerminal*	KeyRightCurlyBracket::clone(void) const
{
	return new KeyRightCurlyBracket(*this);
}
