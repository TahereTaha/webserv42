#include <KeyWordAutoIndex.hpp>

KeyWordAutoIndex::KeyWordAutoIndex(void) : AKeyWord("auto_index")
{
}

KeyWordAutoIndex::~KeyWordAutoIndex(void)
{
}

ATerminal*	KeyWordAutoIndex::clone(void) const
{
	return (new KeyWordAutoIndex(*this));
}

const char	*KeyWordAutoIndex::what(void) const 
{
	return ("auto_index");
}
