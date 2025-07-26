#include <KeyWordRoot.hpp>

KeyWordRoot::KeyWordRoot(void) : AKeyWord("root")
{
}

KeyWordRoot::~KeyWordRoot(void)
{
}

ATerminal*	KeyWordRoot::clone(void) const
{
	return (new KeyWordRoot(*this));
}

const char	*KeyWordRoot::what(void) const 
{
	return ("root");
}
