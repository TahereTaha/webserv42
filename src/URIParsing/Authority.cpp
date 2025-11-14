#include <Authority.hpp>

#include <vector>
#include <string>
#include <stdexcept>
#include <cstring>

#include <tokenize.hpp>
#include <UserInfo.hpp>
#include <utils.hpp>

Authority::Authority(void)
{
	this->_text = "";
}

//	this constructor is incorrect.
Authority::Authority(std::string text)
{
	this->_isUserInfoSet = 0;
	this->_text = text;
}

#include <iostream>

Authority::Authority(	std::vector<std::string>::iterator &iter, \
						std::vector<std::string>::iterator end)
{
	this->_isUserInfoSet = 0;
	//	 check all the no authority cases.

	//	path empty
	if (iter == end || *iter != "/")
		throw (std::invalid_argument("no authhority"));
	iter++;
	if (iter == end || *iter != "/")
		throw (std::invalid_argument("no authhority"));
	iter++;
	//	consume all the tokens in the authority section.
	this->_text = "";
	while (iter != end && *iter != "/" && *iter != "?" && *iter != "#")
	{
		this->_text += *iter;
		iter++;
	}
	this->_tokens = tokenize(this->_text, AUTHORITY_DELIMITERS);

	std::vector<std::string>::iterator	this_iter = this->_tokens.begin();
	std::vector<std::string>::iterator	this_end = this->_tokens.end();

	//	set the user info.
	{
		std::vector<std::string>::iterator	check_point = this_iter;
		try
		{
			this->_userInfo = UserInfo(this_iter, this_end);
			this->_isUserInfoSet = 1;
		}
		catch (std::exception &e)
		{
			if (std::string("no userinfo") != std::string(e.what()))
				throw ;
			this_iter = check_point;
		}
	}
	//	set the host.
	this->_host = Host(this_iter, this_end);

	//	set the port.
	this->_port = 0;
	if (this_iter == this_end)
		return ;
	if (*this_iter != "")
		throw (std::invalid_argument("incorrect port"));
	this_iter++;
	this->_port = stricter_unsigned_stoi(*this_iter, (size_t *)std::string::npos);
	if (this_iter != this_end)
		throw (std::invalid_argument("incorrect authority"));
}

Authority::~Authority(void)
{
}

UserInfo	&Authority::getUserInfo(void)
{
	return (this->_userInfo);
}

Host		&Authority::getHost(void)
{
	return (this->_host);
}

struct sockaddr	*Authority::getSockaddrFromIpLiteral(IpLiteral &ip)
{
	struct sockaddr	*addr;

	addr = (struct sockaddr *) new char[sizeof(struct sockaddr_storage)];
	if (!addr)
		return (NULL);
	if (ip.getType() == IP_V_4)
	{
		struct sockaddr_in *addr_in;

		addr_in = (struct sockaddr_in *) addr;
		addr_in->sin_family = AF_INET;
		addr_in->sin_port = htons(this->_port);
		std::memmove(&(addr_in->sin_addr), ip.getData(), IP_V4_DATA_SIZE);
	}
	else if (ip.getType() == IP_V_4)
	{
		struct sockaddr_in6 *addr_in6;

		addr_in6 = (struct sockaddr_in6 *) addr;
		addr_in6->sin6_family = AF_INET6;
		addr_in6->sin6_port = htons(this->_port);
		std::memmove(&(addr_in6->sin6_addr), ip.getData(), IP_V6_DATA_SIZE);
	}
	return (addr);
}

struct sockaddr	*Authority::getSockaddrFromRegname(std::string name)
{
	(void) name;
	return (NULL);
}

struct sockaddr	*Authority::getSockaddr(void)
{
	if (this->_host.getType() == IP_LITERAL)
		return (getSockaddrFromIpLiteral(this->_host.getIp()));
	else if (this->_host.getType() == REG_NAME)
		return (getSockaddrFromRegname(this->_host.getRegName()));
	return (NULL);
}

