#include <KeyWordLimitExept.hpp>

KeyWordLimitExept::KeyWordLimitExept(void) : AKeyWord("limit_exept")
{
	this->_text = "";
}

KeyWordLimitExept::~KeyWordLimitExept(void)
{
}

ASymbol*	KeyWordLimitExept::clone(void) const
{
	return (new KeyWordLimitExept(*this));
}
