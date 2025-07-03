#include <KeySemicolon.hpp>

KeySemicolon::KeySemicolon(void) : ATerminal()
{
}

Symbol* KeySemicolon::clone(void) const
{
	return (new KeySemicolon(*this));
}

size_t	 KeySemicolon::getTerminalSizeOnStr(const std::string& str)
{
	if (!str.empty() && str[0] == ';')
		return (1);
	return (0);
}
