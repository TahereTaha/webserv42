#include <KeyWordRoot.hpp>

KeyWordRoot::KeyWordRoot(void) : AKeyWord("root")
{
	this->_text = "";
}

KeyWordRoot::~KeyWordRoot(void)
{
}

ASymbol*	KeyWordRoot::clone(void) const
{
	return (new KeyWordRoot(*this));
}
