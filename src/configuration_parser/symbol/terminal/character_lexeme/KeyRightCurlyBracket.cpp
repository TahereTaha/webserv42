#include <KeyRightCurlyBracket.hpp>

KeyRightCurlyBracket::KeyRightCurlyBracket(void) : ATerminal()
{
}

ASymbol*	KeyRightCurlyBracket::clone(void) const
{
	return new KeyRightCurlyBracket(*this);
}

size_t		KeyRightCurlyBracket::getTerminalSizeOnStr(const std::string& str) const 
{
	if (!str.empty() && str[0] == '}')
		return (1);
	return (0);
}
