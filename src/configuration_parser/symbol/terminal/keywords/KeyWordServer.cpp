#include "KeyWordServer.hpp"
#include <cctype>

KeyWordServer::KeyWordServer(void) : AKeyWord("server")
{
}

KeyWordServer::~KeyWordServer(void)
{
}

ATerminal* KeyWordServer::clone() const
{
	return new KeyWordServer(*this);
}

const char	*KeyWordServer::what(void) const
{
	return ("server");
}

