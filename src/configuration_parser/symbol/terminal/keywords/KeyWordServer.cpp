#include "KeyWordServer.hpp"
#include <cctype>

KeyWordServer::KeyWordServer(void) : AKeyWord("server")
{
}

KeyWordServer::~KeyWordServer(void)
{
}

ASymbol* KeyWordServer::clone() const
{
	return new KeyWordServer(*this);
}

