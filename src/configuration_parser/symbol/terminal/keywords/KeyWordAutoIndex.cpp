#include <KeyWordAutoIndex.hpp>

KeyWordAutoIndex::KeyWordAutoIndex(void) : AKeyWord("auto_index")
{
	this->_text = "";
}

KeyWordAutoIndex::~KeyWordAutoIndex(void)
{
}

ASymbol*	KeyWordAutoIndex::clone(void) const
{
	return (new KeyWordAutoIndex(*this));
}
