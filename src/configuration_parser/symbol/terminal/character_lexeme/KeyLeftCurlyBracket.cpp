#include <KeyKeyLeftCurlyBracket.hpp>

KeyLeftCurlyBracket::LeftCurlyBracket(void) : AToken()
{
}

Symbol* KeyLeftCurlyBracket::clone() const
{
    return new KeyLeftCurlyBracket(*this);
}

size_t		 KeyLeftCurlyBracket::getTerminalSizeOnStr(const std::string& str)
{
    if (!str.empty() && str[0] == '{')
		return (1);
	return (0);
}
