#include <KeyWordIndex.hpp>

KeyWordIndex::KeyWordIndex(void) : AKeyWord("index")
{
}

KeyWordIndex::~KeyWordIndex(void)
{
}

ATerminal*	KeyWordIndex::clone(void) const
{
	return (new KeyWordIndex(*this));
}
