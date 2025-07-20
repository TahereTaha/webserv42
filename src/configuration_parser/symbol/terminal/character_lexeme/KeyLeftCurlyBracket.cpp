#include <KeyLeftCurlyBracket.hpp>

KeyLeftCurlyBracket::KeyLeftCurlyBracket(void) : ATerminal()
{
}

KeyLeftCurlyBracket::~KeyLeftCurlyBracket(void)
{
}

ASymbol* KeyLeftCurlyBracket::clone() const
{
    return new KeyLeftCurlyBracket(*this);
}

size_t		 KeyLeftCurlyBracket::getTerminalSizeOnStr(const std::string& str) const 
{
    if (!str.empty() && str[0] == '{')
		return (1);
	return (0);
}
