#include <Host.hpp>

#include <stdexcept>
#include <vector>
#include <string>
#include <cctype>
#include <limits>

#include <tokenize.hpp>

//	helper functions.

static std::string	consume_IP_LITERAL(std::vector<std::string>::iterator &iter, \
		std::vector<std::string>::iterator end)
{
	std::string	text = "";

	if (iter != end)
	{
		text += *iter;
		iter++;
	}
	while (iter != end && *iter != "]")
	{
		text += *iter;
		iter++;
	}
	if (*iter != "]")
		throw (std::invalid_argument("incorrect host"));
	if (iter != end)
	{
		text += *iter;
		iter++;
	}
	return (text);
}

static std::string	consume_REG_NAME(std::vector<std::string>::iterator &iter, \
		std::vector<std::string>::iterator end)
{
	std::string	text = "";
	if (iter != end)
	{
		text += *iter;
		iter++;
	}
	return (text);
}

#define digit_char	"0123456789abcdefghijklmnopqrstuvwxyz"

static int	stoi(std::string num_str, size_t *pos = 0, int base = 10)
{
	size_t	i = 0;
	long	num = 0;
	int		digit = 0;
	int		sign = 1;

	//	skip all the spaces.
	while (i < num_str.size() && isspace(num_str[i]))
		i++;
	if (i < num_str.size() && num_str[i] == '+')
		i++;
	else if (i < num_str.size() && num_str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (i == num_str.size() || !isalnum(num_str[i]))
		throw (std::invalid_argument("not a int"));
	while (i < num_str.size() && isalnum(num_str[i]))
	{
		digit = std::string(digit_char).find(num_str[i]);
		digit *= sign;
		num *= base;
		num += digit;
		if (num > std::numeric_limits<int>::max())
			throw (std::out_of_range("more than max int"));
		if (num < std::numeric_limits<int>::min())
			throw (std::out_of_range("less than min int"));
		i++;
	}
	if (pos != NULL)
		*pos = i;
	return (num);
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
			octet = stoi(text.substr(i), &i);
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
	if (i + 1 != text.size())
		return (0);
	return (1);
}

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
	if  (*iter == "[")
		this->_text = consume_IP_LITERAL(iter, end);
	else
		this->_text = consume_REG_NAME(iter, end);
	this->identifyHostType();
}

Host::~Host(void)
{
}

void	Host::identifyHostType(void)
{
	if (this->_text[0] == '[')
	{
		this->_type = IP_LITERAL;
		if (this->_text[1] == 'v')
			this->_type = IP_LITERAL_V_FUTURE;
		else
			this->_type = IP_LITERAL_V6_ADDRESS;
		if (this->_type == IP_LITERAL_V_FUTURE)
			this->_type = IP_LITERAL_UNSUPORTED;	//	this will be changad to suport more versions
		return ;
	}
	if (is_IPV4address(this->_text))
		this->_type = IP_V4_ADDRESS;
	else
		this->_type = REG_NAME;
}

