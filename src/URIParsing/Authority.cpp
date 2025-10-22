#include <Authority.hpp>

#include <vector>
#include <string>
#include <stdexcept>


Authority::Authority(void)
{
	this->_text = "";
}

Authority::Authority(std::string text)
{
	this->_text = text;
}

Authority::Authority(	std::vector<std::string>::iterator &iter, \
						std::vector<std::string>::iterator end)
{
	std::vector<std::string>::iterator	start = iter;
	if (iter != end && *iter != "/")
	{
		iter = start;
		throw (std::invalid_argument("incorrect authority"));
	}
	iter++;
	if (iter != end && *iter != "/")
	{
		iter = start;
		throw (std::invalid_argument("incorrect authority"));
	}
	iter++;
	this->_text = "";
	while (iter != end && *iter != "/" && *iter != "?" && *iter != "#")
	{
		this->_text += *iter;
		iter++;
	}

//	this->_userInfo = UserInfo();
//	this->_host = Host();
//	this->_port = Port();
}

Authority::~Authority(void)
{
}

