#include <IpLiteral.hpp>

#include <stdexcept>
#include <limits>
#include <cstring>
#include <stdint.h>

#include <utils.hpp>
#include <tokenize.hpp>

//	helper functions.

static void	read_ipv4_octets(std::string text, uint8_t *data_buff)
{
	size_t	octet_count = 0;
	size_t	i = 0;

	unsigned int	num = 0;

	while (i < text.size() && octet_count < IP_V4_DATA_SIZE)
	{
		num = stricter_unsigned_stoi(text, &i);
		if (std::numeric_limits<unsigned char>::max() < num)
			throw (std::invalid_argument("incorrect octet"));
		data_buff[octet_count] = num;
		if (i < text.size() && text[i] != '.')
			throw (std::invalid_argument("incorrect ipv4"));
		octet_count++;
		i++;
	}
	if (i < text.size() || octet_count < IP_V4_DATA_SIZE)
		throw (std::invalid_argument("incorrect ipv4"));
}

static size_t	read_ipv6_first_octets(std::vector<std::string> tokens, uint8_t *data_buff)
{
	size_t	i = 0;
	size_t	octet_count = 0;
	uint16_t	piece_num = 0;

	if (tokens[0] == ":")
		throw (std::invalid_argument("incorrect ipv6"));
	while (i < tokens.size() && octet_count < IP_V6_DATA_SIZE)
	{
		if (tokens[i] == ":" && tokens[i + 1] == ":")
			return (octet_count);
		if (tokens[i] != ":")
		{
			// check if the last two pieces are replaced by a ipv4.
			if (octet_count == 12 && tokens[i].find('.') != std::string::npos)
			{
				try
				{
					read_ipv4_octets(tokens[i], &(data_buff[octet_count]));
				}
				catch (...)
				{
					throw (std::invalid_argument("incorrect ipv6"));
				}
				octet_count += 4;
				break ;
			}
			piece_num = stricter_unsigned_stoi(tokens[i], (size_t *)std::string::npos, 16);
			data_buff[octet_count] = piece_num >> 8;
			data_buff[octet_count] = piece_num;
		}
		i++;
	}
	if (octet_count == IP_V6_DATA_SIZE && i + 1 == tokens.size())
		throw (std::invalid_argument("incorrect ipv6"));
	return (octet_count);
}

static size_t	read_ipv6_last_octets(std::vector<std::string> tokens, uint8_t *data_buff)
{
	size_t	i = 1;
	size_t	octet_count = 0;
	uint16_t	piece_num = 0;

	//	iterate to where the end starts.
	while (i < tokens.size())
	{
		if (tokens[i] == ":" && tokens[i - 1] == ":")
			break ;
		i++;
	}
	while (i < tokens.size() && octet_count < IP_V6_DATA_SIZE)
	{
		if (tokens[i] != ":")
		{
			// check if the last two pieces are replaced by a ipv4.
			if (tokens.size() == i + 1 && tokens[i].find('.') != std::string::npos)
			{
				try
				{
					read_ipv4_octets(tokens[i], &(data_buff[octet_count]));
				}
				catch (...)
				{
					throw (std::invalid_argument("incorrect ipv6"));
				}
				return (IP_MAX_DATA_SIZE);
			}
			piece_num = stricter_unsigned_stoi(tokens[i], (size_t *)std::string::npos, 16);
			data_buff[octet_count] = piece_num >> 8;
			data_buff[octet_count] = piece_num;
		}
		i++;
	}
	if (octet_count == IP_V6_DATA_SIZE)
		throw (std::invalid_argument("incorrect ipv6"));
	return (octet_count);
}

static void	read_ipv6_octets(std::string text, uint8_t *data_buff)
{
	//		make some syntax checks.

	//	check that it is enclosed by [].
	if (text[0] != '[' || text[text.size() - 1] != ']')
		throw (std::invalid_argument("incorrect ipv6"));
	//	check that there are no three : in secuence.
	if (text.find(":::") != std::string::npos)
		throw (std::invalid_argument("incorrect ipv6"));
	//	check that there are no two diferent :: in the ipv6.
	if (text.find("::") != text.rfind("::"))
		throw (std::invalid_argument("incorrect ipv6"));

	// preproses the text string.

	text = text.substr(1, text.size() - 2);
	std::vector<std::string> tokens = tokenize(text, ":");

	//	write the content to octets.

	uint8_t	first_octets[IP_MAX_DATA_SIZE];
	size_t	first_octets_size = 0;
	std::memset(first_octets, 0, IP_MAX_DATA_SIZE);

	uint8_t	last_octets[IP_MAX_DATA_SIZE];
	size_t	last_octets_size = 0;
	std::memset(last_octets, 0, IP_MAX_DATA_SIZE);

	first_octets_size = read_ipv6_first_octets(tokens, first_octets);
	std::memmove(data_buff, first_octets, first_octets_size);
	if (first_octets_size != IP_MAX_DATA_SIZE)
		last_octets_size = read_ipv6_last_octets(tokens, last_octets);
	if (first_octets_size + last_octets_size >= IP_MAX_DATA_SIZE)
		throw (std::invalid_argument("incorrect ipv6"));
	std::memmove(data_buff + IP_MAX_DATA_SIZE - last_octets_size, last_octets, last_octets_size);
}

//	class methods.

IpLiteral::IpLiteral(void)
{
}

IpLiteral::IpLiteral(std::string text)
{
	this->_text = text;
	this->identifyType();
	if (this->_type == IP_V_FUTURE)
		throw (std::invalid_argument("ip literal unsuported"));
	if (this->_type == IP_V_4)
		read_ipv4_octets(this->_text, this->_data);
	if (this->_type == IP_V_6)
		read_ipv6_octets(this->_text, this->_data);
}

IpLiteral::~IpLiteral(void)
{
}

void	IpLiteral::identifyType(void)
{
	this->_type = IP_V_4;
	if (this->_text.size() < 3)
		return ;
	if (this->_text[0] == '[')
		this->_type = IP_V_6;
	if (this->_text[0] == '[' && this->_text[1] == 'v')
		this->_type = IP_V_FUTURE;
	if (this->_text[0] != '[')
		this->_type = IP_V_4;
}

t_IpLiteral_type	IpLiteral::getType(void) const
{
	return (this->_type);
}

uint8_t				*IpLiteral::getData(void)
{
	return (this->_data);
}

#include <iostream>
#include <ios>

static void	print_ipv4(uint8_t *data)
{
	size_t	i = 0;
	while (i < IP_V4_DATA_SIZE)
	{
		std::cout << (int)data[i];
		if (i + 1 != IP_V4_DATA_SIZE)
			std::cout << ".";
		i++;
	}
	std::cout << std::endl;
}

static void	print_ipv6(uint8_t *_data)
{
	size_t	i = 0;
	uint16_t	*data = _data;
	while (i < IP_V6_DATA_SIZE / 2)
	{
		std::cout << std::hex << (int) data[i];
		if (i + 1 != IP_V6_DATA_SIZE / 2)
			std::cout << ":";
		i++;
	}
	std::cout << std::dec << std::endl;
}

void	IpLiteral::print(void) const
{
	if (this->_type == IP_V_4)
		print_ipv4(this->_data);
	else
		print_ipv6(this->_data);
}

