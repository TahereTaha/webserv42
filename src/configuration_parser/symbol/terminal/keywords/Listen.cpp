#include <Listen.hpp>
#include <cctype>

Listen::Listen(void)
{
	this->_text = "";
}

Listen::Listen(std::string str)
{
	
	if (str.length() > 5 && str.substr(0, 5) == "listen")
		this->_text = str.substr(0, 5);
	else
		this->_text = "";
}

Listen::Listen(const Listen& other)
{
	*this = other;
}

Listen& Listen::operator=(const Listen& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

