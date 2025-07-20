#include <KeyWordIndex.hpp>

KeyWordIndex::KeyWordIndex(void) : AKeyWord("index")
{
	this->_text = "";
}

KeyWordIndex::~KeyWordIndex(void)
{
}

ASymbol*	KeyWordIndex::clone(void) const
{
	return (new KeyWordIndex(*this));
}
