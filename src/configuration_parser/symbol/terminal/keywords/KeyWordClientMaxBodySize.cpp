#include <KeyWordClientMaxBodySize.hpp>

KeyWordClientMaxBodySize::KeyWordClientMaxBodySize(void) : AKeyWord("client_max_body_size")
{
}

KeyWordClientMaxBodySize::~KeyWordClientMaxBodySize(void)
{
}

ATerminal*	KeyWordClientMaxBodySize::clone(void) const
{
	return (new KeyWordClientMaxBodySize(*this));
}
