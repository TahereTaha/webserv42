#include <percent_encoding_utils.hpp>

#include <assert.h>

#include <cctype>
#include <string>
#include <sstream>
#include <stdexcept>

//	this assumes that the input is correct.
static unsigned int	hex_to_int(std::string text)
{
	size_t	i = 0;
	size_t	value = 0;
	while (i < text.size())
	{
		value *= 16;
		if (text[i] >= '0' && text[i] <= '9')
			value += text[i] - '0';
		else if (text[i] >= 'A' && text[i] <= 'F')
			value += text[i] - '0';
		i++;
	}
	return (value);
}

int	is_pct_encoded(std::string text)
{
	if (text.size() < 3)
		return (0);
	if (text[0] != '%')
		return (0);
	if (!isxdigit(text[1]))
		return (0);
	if (!isxdigit(text[2]))
		return (0);
	return (1);
}

//	this assumes that the pct_encoded is correct.
static std::string	normalize_pct_encoded(std::string text)
{
	text[1] = std::toupper(text[1]);
	text[2] = std::toupper(text[2]);

	return (text);
}

static std::string	decode_pct_encoded(std::string text)
{
	assert(is_pct_encoded(text));
	text = normalize_pct_encoded(text);

	char	c = hex_to_int(text.substr(1, 2));
	std::string	return_val = "";
	return_val.push_back(c);
	return (return_val);
}

std::string	decode_pct_encoded_string(std::string text)
{
	std::string	return_val = "";
	size_t	i = 0;
	while (i < text.size())
	{
		//	append one character to the output string.
		if (is_pct_encoded(text))
			return_val += decode_pct_encoded(text.substr(i, std::string::npos));
		else if (text[i] != '%')
			return_val += text[i];
		else
			throw (malformed_pct_encoding("malformed pct_encoding"));
		//	iterate over the original string.
		if (text[i] == '%')
			i += 3;
		else
			i++;
	}
	return (return_val);
}

static std::string	hex_to_str(unsigned int hex)
{
	std::string	hex_str = "";
	char	c;
	while (hex)
	{
		c = hex % 16;
		hex_str = std::string(1, c) + hex_str;
		hex /= 16;
	}
	return (hex_str);
}

static std::string	encode_pct(unsigned int c)
{
	std::string	pct_str = "%" + hex_to_str(c);
	return (pct_str);
}

std::string	encode_to_pct_encoding(std::string text, std::string reserved_chars)
{
	std::string	return_val = "";
	size_t	i = 0;
	while (i < text.size())
	{
		if (isgraph(text[i]) && reserved_chars.find(text[i]) == std::string::npos && text[i] != '%')
			return_val += text[i];
		else
			return_val += encode_pct(text[i]);
		i++;
	}
	return (return_val);
}

