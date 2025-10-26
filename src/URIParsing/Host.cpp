#include <Host.hpp>

#include <stdexcept>
#include <vector>
#include <string>
#include <cctype>
#include <limits>

#include <tokenize.hpp>

//	helper functions.

static std::string	consume_REG_NAME(std::vector<std::string>::iterator &iter, \
		std::vector<std::string>::iterator end)
{
}


static int	is_IPV4address(std::string text)
{
	size_t	i = 0;
	int		octet;
	size_t	octet_count= 0;
	while (i < text.size() && octet_count < 4)
	{
		try
		{
			octet = stricter_unsigned_stoi(text.substr(i), &i);
		}
		catch (...)
		{
			return (0);
		}
		if (octet < 0 || octet > 255)
			return (0);
		if (i < text.size())
		{
			if (text[i] != '.')
				return (0);
			i++;
		}
		octet_count++;
	}
	if (i < text.size())
		return (0);
	if (octet_count != 4)
		return (0);
	return (1);
}

//static int	is_IPV6address(std::string text)
//{
//	if (text[0] != '[' || text[text.size() - 1] != ']')		//	check if it is enclosed in []
//		return (0);
//	text = text.substr(1, text.size() - 2);
//	std::vector<std::string>	tokens = tokenize(text, ":");
//	//	check the last part is formated correctly if it is a ipv4
//	if (is_ipv4_least_significant_section && !isIPV4address(tokens[tokens.size() - 1]))
//		return (0);
//
//	size_t	i = 0;
//	size_t	groups_of_16bit = 0;
//	while (i < tokens.size() && groups_of_16bit < 8)
//	{
//		if (i + 1 == token.size() && )
//		i++;
//	}
//	return (1);
//}


//	class methods.

Host::Host(void)
{
}

Host::Host(std::string text)
{
	this->_text = text;
	this->identifyHostType();
}

//	the logic for identifing the host type is duplicated 
//	here too, for consuming only  the nesesary tokens
Host::Host(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end)
{
	this->_text = "";
	if (this->_text[0] == '[')
		throw (std::invalid_argument("unsuported ip format"));
	if (iter != end && *iter != ":")
	{
		text += *iter;
		iter++;
	}
	this->identifyHostType();
}

Host::~Host(void)
{
}

void	Host::identifyHostType(void)
{
	if (is_IPV4address(this->_text))
		this->_type = IP_V4_ADDRESS;
	else
		this->_type = REG_NAME;
}

