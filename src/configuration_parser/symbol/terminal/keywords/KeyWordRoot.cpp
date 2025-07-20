#include <KeyWordRoot.hpp>

KeyWordRoot::KeyWordRoot(void) : AKeyWord("root")
{
}

KeyWordRoot::~KeyWordRoot(void)
{
}

ASymbol*	KeyWordRoot::clone(void) const
{
	return (new KeyWordRoot(*this));
}
