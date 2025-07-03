#include "KeyWordServer.hpp"
#include <cctype>

KeyWordServer::KeyWordServer(void) : ATerminal()
{
}

KeyWordServer::KeyWordServer(const KeyWordServer& other)
{
	*this = other;
}

KeyWordServer& KeyWordServer::operator=(const KeyWordServer& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

Symbol* KeyWordServer::clone() const
{
	return new KeyWordServer(*this);
}

size_t  KeyWordServer::getTerminalSizeOnStr(const std::string & str)
{
	size_t size = 0;
	if (str.length() > 5 && str.substr(0, 5) == "server")
		size = 6;
	return size;

}

