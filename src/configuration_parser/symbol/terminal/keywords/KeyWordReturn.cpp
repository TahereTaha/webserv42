#include "KeyWordReturn.hpp"
#include <cctype>

KeyWordReturn::KeyWordReturn(void) :AKeyWord("return")
{
}

KeyWordReturn::~KeyWordReturn(void)
{
}

ATerminal* KeyWordReturn::clone() const
{
	return new KeyWordReturn(*this);
}

const char	*KeyWordReturn::what(void) const 
{
	return ("return");
}
