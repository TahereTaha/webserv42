#include <KeyRightCurlyBracket.hpp>

KeyRightCurlyBracket::KeyRightCurlyBracket(void) : AKeyWord("}")
{
}

KeyRightCurlyBracket::~KeyRightCurlyBracket(void)
{
}

ASymbol*	KeyRightCurlyBracket::clone(void) const
{
	return new KeyRightCurlyBracket(*this);
}
