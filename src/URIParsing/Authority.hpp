#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <UserInfo.hpp>
#include <Host.hpp>

#define AUTHORITY_DELIMITERS "@:[]"

class Authority
{
	private:
		std::string	_text;
		std::vector<std::string>	_tokens;

		int			_isUserInfoSet;
		UserInfo	_userInfo;
		Host		_host;
		uint16_t	_port;

		struct sockaddr	*getSockaddrFromIpLiteral(IpLiteral &ip);
		struct sockaddr	*getSockaddrFromRegname(std::string name);
	protected:
	public:
		Authority(void);
		Authority(std::string text);
		Authority(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end);
		~Authority(void);

		UserInfo	&getUserInfo(void);
		Host		&getHost(void);
		uint16_t	&getPort(void);
		struct sockaddr	*getSockaddr(void) ;
};

