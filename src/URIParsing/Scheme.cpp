#include <Scheme.hpp>

#include <string>
#include <vector>
#include <stdexcept>

#include <URI.hpp>

Scheme::Scheme(void)
{
	this->_text = "";
	this->setScheme();
}

Scheme::Scheme(std::string text)
{
	this->_text = text;
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
	this->setScheme();
}

Scheme::~Scheme(void)
{
}

//
//int		Scheme::isSchemeTextValid(void) const 
//{
//	if (this->_text.size() == 0)
//		throw (std::invalid_argument(""));
//
//
//	size_t	i = 0;
//	while (i < this->_text.size())
//	{
//		if ()
//			throw (std::invalid_argument(""));
//		i++;
//	}
//}

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

