#include <UserInfo.hpp>

#include <vector>
#include <string>

#include <URI.hpp>
#include <percent_encoding_utils.hpp>

//	helper functions.

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

//	class methods.

UserInfo::UserInfo(void)
{
	this->_isPasswordSet = 0;
}

UserInfo::UserInfo(std::string text)
{
	this->_text = text;
	this->fillUserAndPassword();
	this->normalize();
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
	this->fillUserAndPassword();
	this->normalize();
}

UserInfo::~UserInfo(void)
{
}

void	UserInfo::fillUserAndPassword(void)
{
	size_t	password_delimiter = this->_text.find(':');
	if (password_delimiter == std::string::npos)
	{
		this->_user = this->_text.substr(0, password_delimiter);
		this->_password = this->_text.substr(password_delimiter + 1, std::string::npos);
		this->_isPasswordSet = 1;
	}
	else
	{
		this->_user = this->_text;
		this->_password = "";
		this->_isPasswordSet = 0;
	}
}

void	UserInfo::normalize(void)
{
	this->_user = decode_pct_encoded_string(this->_user);
	this->_password = decode_pct_encoded_string(this->_password);
}

std::string	UserInfo::getUse(void) const
{
	return (this->_user);
}

std::string	UserInfo::getPassword(void) const
{
	return (this->_password);
}

