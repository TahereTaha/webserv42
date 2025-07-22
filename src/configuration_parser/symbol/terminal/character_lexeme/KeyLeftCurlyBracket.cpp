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
