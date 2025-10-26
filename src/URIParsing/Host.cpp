#include <Host.hpp>

#include <stdexcept>
#include <vector>
#include <string>


//	class methods.

Host::Host(void)
{
}

Host::Host(std::string text)
{
	this->_text = text;
}

Host::Host(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end)
{
	this->_text = "";
	std::string	text_at_check_point = this->_text;
	std::vector<std::string>::iterator	start = iter;
	std::vector<std::string>::iterator	check_point = iter;

	while (iter != end)
	{
		if (*iter == ":")
		{
			check_point = iter;
			text_at_check_point = this->_text;
		}
		this->_text = *iter;
		iter++;
	}
	if (check_point != start)
	{
		this->_text = text_at_check_point;
		iter = check_point;
	}
	if (this->_text == "")
		throw (std::invalid_argument("no host"));
	
}

Host::~Host(void)
{
}
