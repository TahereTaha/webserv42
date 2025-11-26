#include <Host.hpp>

#include <stdexcept>
#include <vector>
#include <string>

#include <percent_encoding_utils.hpp>

#include <IpLiteral.hpp>

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

	if (*iter == "[")
	{
		while (iter != end && *iter != "]")
		{
			this->_text += *iter;
			iter++;
		}
		if (iter == end)
			throw (std::invalid_argument("incorrect ipv6"));
		this->_text += *iter;
	}
	else
	{
		this->_text = *iter;
		iter++;
	}
	if (this->_text == "")
		throw (std::invalid_argument("no host"));
	try
	{
		this->_ip = IpLiteral(this->_text);
		this->_type = IP_LITERAL;
	}
	catch (std::exception &e)
	{
		if (std::string(e.what()) == std::string("ip literal unsuported"))
			throw ;
		if (this->_text[0] == '[')
			throw ;
		this->_type = REG_NAME;
		this->_text = decode_pct_encoded_string(this->_text);
	}
}

Host::~Host(void)
{
}

t_host_type	Host::getType(void) const 
{
	return (this->_type);
}

std::string	Host::getRegName(void) const 
{
	if (this->_type != REG_NAME)
		throw (std::out_of_range("not a reg name"));
	return (this->_text);
}

IpLiteral	&Host::getIp()
{
	if (this->_type != IP_LITERAL)
		throw (std::out_of_range("not a ip literal"));
	return (this->_ip);
}

