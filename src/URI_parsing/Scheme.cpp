#include <Scheme.hpp>

#include <string>
#include <vector>
#include <stdexcept>

#include <URI.hpp>
#include <percent_encoding_utils.hpp>

Scheme::Scheme(void)
{
	this->_text = "";
	this->setScheme();
}

Scheme::Scheme(std::string text)
{
	this->_text = text;
	this->normalizeText();
	this->checkSchemeTextValid();
	this->setScheme();
}

Scheme::Scheme(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end)
{
	if (iter == end)
		throw (std::invalid_argument("reached a delimiter without finding a scheme."));
	if (std::string(gen_delims).find(*iter) != std::string::npos)
		throw (std::invalid_argument("reached a delimiter without finding a scheme."));
	this->_text = *iter;
	iter++;
	this->normalizeText();
	this->checkSchemeTextValid();
	this->setScheme();
}

Scheme::~Scheme(void)
{
}

void	Scheme::normalizeText(void)
{
	this->_text = decode_pct_encoded_string(this->_text);
	size_t	i = 0;
	while (i < this->_text.size())
	{
		this->_text[i] = tolower(this->_text[i]);
		i++;
	}
}

static int	is_scheme_char(int c)
{
	if (isalnum(c))
		return (1);
	if (c == '+')
	   return (1);
	if (c == '-')
	   return (1);
	if (c == '.')
	   return (1);
	return (0);
}

void		Scheme::checkSchemeTextValid(void) const 
{
	if (this->_text.size() == 0)
		throw (std::invalid_argument("incorrect scheme"));

	if (!isalpha(this->_text[0]))
		throw (std::invalid_argument("incorrect scheme"));
	size_t	i = 0;
	while (i < this->_text.size())
	{
		if (!is_scheme_char(this->_text[i]))
			throw (std::invalid_argument("incorrect scheme"));
		i++;
	}
}

const static char *scheme_strings[] = \
{\
	"file", \
	"ftp", \
	"http", \
	"https", \
	"mailto", \
	"tel", \
	"imap", \
	"irc", \
	"nntp", \
	"acap", \
	"icap", \
	"mtqp", \
	"wss", \
	NULL \
};

void	Scheme::setScheme(void)
{
	size_t	i = 0;
	while (scheme_strings[i])
	{
		if (scheme_strings[i] == this->_text)
		{
			this->_scheme = (t_uri_scheme)i;
			return ;
		}
		i++;
	}
	this->_scheme = scheme_UNOFFICIAL;
}

t_uri_scheme	Scheme::getSchemeType(void) const 
{
	return (this->_scheme);
}

int		operator == (const t_uri_scheme &scheme_1, const Scheme &scheme_2)
{
	if (scheme_1 == scheme_2.getSchemeType())
		return (1);
	return (0);
}

int		operator == (const Scheme &scheme_1, const t_uri_scheme &scheme_2)
{
	if (scheme_2 == scheme_1.getSchemeType())
		return (1);
	return (0);
}

int		operator != (const t_uri_scheme &scheme_1, const Scheme &scheme_2)
{
	if (scheme_1 != scheme_2.getSchemeType())
		return (1);
	return (0);
}

int		operator != (const Scheme &scheme_1, const t_uri_scheme &scheme_2)
{
	if (scheme_2 != scheme_1.getSchemeType())
		return (1);
	return (0);
}

