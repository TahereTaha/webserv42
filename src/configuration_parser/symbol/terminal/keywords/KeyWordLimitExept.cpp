#include <KeyWordLimitExept.hpp>

KeyWordLimitExept::KeyWordLimitExept(void) : AKeyWord("limit_exept")
{
}

KeyWordLimitExept::~KeyWordLimitExept(void)
{
}

ATerminal*	KeyWordLimitExept::clone(void) const
{
	return (new KeyWordLimitExept(*this));
}

const char	*KeyWordLimitExept::what(void) const 
{
	return ("limit_exept");
}
