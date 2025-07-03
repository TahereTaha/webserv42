#include <KeyRightCurlyBracket.hpp>

KeyRightCurlyBracket::KeyRightCurlyBracket(void) : ATerminal()
{
}

ATerminal*	KeyRightCurlyBracket::clone(void) const
{
	return new KeyRightCurlyBracket(*this);
}

size_t		KeyRightCurlyBracket::getTerminalSizeOnStr(const std::string& str)
{
	if (!str.empty() && str[0] == '}')
		return (1);
	return (0);
}
