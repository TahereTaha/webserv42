#include <KeyWordLocation.hpp>

KeyWordLocation::KeyWordLocation(void) : AKeyWord("location")
{
	this->_text = "";
}

KeyWordLocation::~KeyWordLocation(void)
{
}

ASymbol*	KeyWordLocation::clone(void) const
{
	return (new KeyWordLocation(*this));
}
