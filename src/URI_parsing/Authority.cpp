#include <Authority.hpp>

#include <vector>
#include <string>
#include <stdexcept>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

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
	if (*this_iter != ":")
		throw (std::invalid_argument("incorrect port"));
	this_iter++;
	this->_port = htons((uint16_t)stricter_unsigned_stoi(*this_iter, (size_t *)std::string::npos));
	this->_isPortSet = 1;
	this_iter++;
	if (this_iter != this_end)
		throw (std::invalid_argument("incorrect authority"));
}

#include <iostream>

Authority::Authority(	std::vector<std::string>::iterator &iter, \
						std::vector<std::string>::iterator end)
{
	this->_isUserInfoSet = 0;
	this->_isPortSet = 0;
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
	if (*this_iter != ":")
		throw (std::invalid_argument("incorrect port"));
	this_iter++;
	this->_port = stricter_unsigned_stoi(*this_iter, (size_t *)std::string::npos);
	this->_isPortSet = 1;
	this_iter++;
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

uint16_t	Authority::getPort(void)
{
	if (this->_isPortSet != 1)
		throw (std::out_of_range("unset port"));
	return (this->_port);
}

std::vector<struct sockaddr *>	Authority::getSockaddrFromIpLiteral(IpLiteral &ip)
{
	struct sockaddr	*addr;

	addr = (struct sockaddr *) new char[sizeof(struct sockaddr_storage)];
	if (!addr)
		return (std::vector<struct sockaddr *>());
	if (ip.getType() == IP_V_4)
	{
		struct sockaddr_in *addr_in;

		addr_in = (struct sockaddr_in *) addr;
		addr_in->sin_family = AF_INET;
		if (this->_isPortSet == 1)
			addr_in->sin_port = this->_port;
		else
			addr_in->sin_port = htons(80);
		std::memmove(&(addr_in->sin_addr), ip.getData(), IP_V4_DATA_SIZE);
	}
	else if (ip.getType() == IP_V_4)
	{
		struct sockaddr_in6 *addr_in6;

		addr_in6 = (struct sockaddr_in6 *) addr;
		addr_in6->sin6_family = AF_INET6;
		if (this->_isPortSet == 1)
			addr_in6->sin6_port = this->_port;
		else
			addr_in6->sin6_port = htons(80);
		std::memmove(&(addr_in6->sin6_addr), ip.getData(), IP_V6_DATA_SIZE);
	}

	std::vector<struct sockaddr *>	res;
	res.push_back(addr);
	return (res);
}

static std::vector<struct sockaddr *>	get_addresses(struct addrinfo *addr_info, int is_port_set, uint16_t port)
{
	std::vector<struct sockaddr *>	res;
	struct sockaddr	*addr;

	while (addr_info)
	{
		addr = (struct sockaddr *) new char[sizeof(struct sockaddr_storage)];
		if (!addr)
		{
			size_t i = 0;
			while (i < res.size())
			{
				delete[] (char *) res[i];
				i++;
			}
			return (std::vector<struct sockaddr *>());
		}
		if (addr_info->ai_addr->sa_family == AF_INET)
			std::memmove(addr, addr_info->ai_addr, sizeof(struct sockaddr_in));
		else if (addr_info->ai_addr->sa_family == AF_INET6)
			std::memmove(addr, addr_info->ai_addr, sizeof(struct sockaddr_in6));
		
		res.push_back(addr);

		addr_info = addr_info->ai_next;
	}
	size_t	i = 0;
	while (i < res.size())
	{
		struct sockaddr_in	*addr_in;
		addr_in = (struct sockaddr_in *)res[i];
		if (is_port_set)
			addr_in->sin_port = port;
		else
			addr_in->sin_port = htons(80);
		i++;
	}

	return (res);
}

std::vector<struct sockaddr *>	Authority::getSockaddrFromRegname(std::string name)
{
	struct addrinfo	*res = NULL;

	struct addrinfo hint;
	std::memset(&hint, 0, sizeof(struct addrinfo));

	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;

	int	error = getaddrinfo(name.c_str(), NULL, &hint, &res);
	if (error)
		throw (std::invalid_argument("incorrect name"));

	std::vector<struct sockaddr *>	addresses;
	addresses = get_addresses(res, this->_isPortSet, this->_port);
	freeaddrinfo(res);
	return (addresses);
}

std::vector<struct sockaddr *>	Authority::getSockaddr(void)
{
	if (this->_host.getType() == IP_LITERAL)
		return (getSockaddrFromIpLiteral(this->_host.getIp()));
	else if (this->_host.getType() == REG_NAME)
		return (getSockaddrFromRegname(this->_host.getRegName()));
	return (std::vector<struct sockaddr *>());
}

