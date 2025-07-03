#include "Server.hpp"
#include <cctype>

Server::Server(void)
{
	this->_text = "";
}

Server::Server(std::string str)
{
	setText(str);
}

Server::Server(const Server& other)
{
	*this = other;
}

Server& Server::operator=(const Server& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

Symbol* Server::clone() const
{
	return new Server(*this);
}

void Server::setText(const std::string& str)
{
	if (str.length() > 5 && str.substr(0, 5) == "server")
		this->_text = str.substr(0, 5);
	else
		this->_text = "";
}

