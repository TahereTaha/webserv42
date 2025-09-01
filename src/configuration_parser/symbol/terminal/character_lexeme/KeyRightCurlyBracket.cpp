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

const char	*KeyRightCurlyBracket::what(void) const 
{
	return ("right_curly_bracket");
}
