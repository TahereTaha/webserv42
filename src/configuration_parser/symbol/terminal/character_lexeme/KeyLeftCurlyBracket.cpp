#include <KeyLeftCurlyBracket.hpp>

KeyLeftCurlyBracket::KeyLeftCurlyBracket(void) : AKeyWord("{")
{
}

KeyLeftCurlyBracket::~KeyLeftCurlyBracket(void)
{
}

ATerminal* KeyLeftCurlyBracket::clone() const
{
    return new KeyLeftCurlyBracket(*this);
}

const char	*KeyLeftCurlyBracket::what(void) const 
{
	return ("left_curly_bracket");
}
