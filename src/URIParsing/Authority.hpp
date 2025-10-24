#pragma once

#include <vector>
#include <string>

#include <UserInfo.hpp>

#define AUTHORITY_DELIMITERS "@:"

class Authority
{
	private:
		std::string	_text;
		std::vector<std::string>	_tokens;

		int			_isUserInfoSet;
		UserInfo	_userInfo;
//		Host		_host;
//		Port		_port;

	protected:
	public:
		Authority(void);
		Authority(std::string text);
		Authority(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end);
		~Authority(void);

		UserInfo	&getUserInfo(void);
//		Host		&getHost(void);
//		Port		&getPort(void);
};

