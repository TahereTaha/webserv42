#include "ErrorPage.hpp"
#include <cctype>

ErrorPage::ErrorPage(void)
{
	this->_text = "";
}

ErrorPage::ErrorPage(std::string str)
{
	if (str.length() > 9 && str.substr(0, 9) == "error_page")
		this->_text = str.substr(0, 9);
	else
		this->_text = "";
}

ErrorPage::ErrorPage(const ErrorPage& other)
{
	*this = other;
}

ErrorPage& ErrorPage::operator=(const ErrorPage& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

