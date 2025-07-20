#include "KeyWordServer.hpp"
#include <cctype>

KeyWordServer::KeyWordServer(void) : ATerminal()
{
}

ASymbol* KeyWordServer::clone() const
{
	return new KeyWordServer(*this);
}

size_t  KeyWordServer::getTerminalSizeOnStr(const std::string & str) const 
{
	size_t size = 0;
	if (str.length() > 5 && str.substr(0, 5) == "server")
		size = 6;
	return size;

}

