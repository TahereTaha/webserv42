#include <KeyWordAutoIndex.hpp>

KeyWordAutoIndex::KeyWordAutoIndex(void) : AKeyWord("auto_index")
{
}

KeyWordAutoIndex::~KeyWordAutoIndex(void)
{
}

ASymbol*	KeyWordAutoIndex::clone(void) const
{
	return (new KeyWordAutoIndex(*this));
}
