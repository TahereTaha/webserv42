#include <KeyWordLocation.hpp>

KeyWordLocation::KeyWordLocation(void) : AKeyWord("location")
{
}

KeyWordLocation::~KeyWordLocation(void)
{
}

ATerminal*	KeyWordLocation::clone(void) const
{
	return (new KeyWordLocation(*this));
}
