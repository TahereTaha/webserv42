#include <UserInfo.hpp>

#include <vector>
#include <string>

#include <URI.hpp>

UserInfo::UserInfo(void)
{
}

UserInfo::UserInfo(std::string text)
{
	this->_text = text;
}

//	it will return a iterator to the position of the @ if it finds one delimiting the user info.
//	else it will return end.
static std::vector<std::string>::iterator	get_at_sign_delimiter(	\
											std::vector<std::string>::iterator &iter, \
											std::vector<std::string>::iterator end)
{
	std::vector<std::string>::iterator start = iter;

	while (iter != end && *iter != "@" && *iter != "/")
	{
		iter++;
	}
	if (iter == end || *iter == "/")
	{
		iter = start;
		return (end);
	}
	std::vector<std::string>::iterator at_sign = iter;
	iter == start;
	return (at_sign);
}

UserInfo::UserInfo(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end)
{
	this->_text = "";
	std::vector<std::string>::iterator	at_sign = get_at_sign_delimiter(iter, end);
	if (at_sign == end)
		return ;
	while (iter <= at_sign)
	{
		this->_text += *iter;
		iter++;
	}
}

UserInfo::~UserInfo(void)
{
}

