#include <Authority.hpp>

#include <vector>
#include <string>
#include <stdexcept>

#include <tokenize.hpp>
#include <UserInfo.hpp>

Authority::Authority(void)
{
	this->_text = "";
}

Authority::Authority(std::string text)
{
	this->_isUserInfoSet = 0;
	this->_text = text;
}

Authority::Authority(	std::vector<std::string>::iterator &iter, \
						std::vector<std::string>::iterator end)
{
	this->_isUserInfoSet = 0;
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
	this->_tokens = tokenize(this->_text, AUTHORITY_DELIMITERS);

	std::vector<std::string>::iterator	this_start = this->_tokens.begin();
	std::vector<std::string>::iterator	this_iter = this_start;
	std::vector<std::string>::iterator	this_end = this->_tokens.end();

	this->_userInfo = UserInfo(this_iter, this_end);
	if (this_iter != this_start)
		this->_isUserInfoSet = 1;
//	this->_host = Host();
//	this->_port = Port();
}

Authority::~Authority(void)
{
}

UserInfo	&Authority::getUserInfo(void)
{
	return (this->_userInfo);
}

