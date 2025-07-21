#include <KeyLeftCurlyBracket.hpp>

KeyLeftCurlyBracket::KeyLeftCurlyBracket(void) : AKeyWord("{")
{
}

KeyLeftCurlyBracket::~KeyLeftCurlyBracket(void)
{
}

ASymbol* KeyLeftCurlyBracket::clone() const
{
    return new KeyLeftCurlyBracket(*this);
}
