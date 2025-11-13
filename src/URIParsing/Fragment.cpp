#include <Fragment.hpp>

#include <string>
#include <vector>
#include <stdexcept>

#include <percent_encoding_utils.hpp>
#include <URI.hpp>

//	helper functions.

static int	is_pchar(int c)
{
	//	unreserved.
	if (std::isalnum(c))
		return (1);
	if (std::string(UNRESERVED).find(c) != std::string::npos)
		return (1);
	//	sub delims.
	if (std::string(sub_delims).find(c) != std::string::npos)
		return (1);
	//	pchar characters.
	if (std::string(PCHAR).find(c) != std::string::npos)
		return (1);
	return (0);
}

//	class methods.

Fragment::Fragment(void)
{
}

Fragment::Fragment(std::string text)
{
	if (text[0] != '?')
		throw (std::invalid_argument("no fragment"));
	this->_text = text.substr(1);
	this->checkFragmentText();
}

Fragment::Fragment(std::vector<std::string>::iterator &iter,std::vector<std::string>::iterator end)
{
	if (*iter != "#")
		throw (std::invalid_argument("no fragment"));
	iter++;
	this->_text = "";
	while (iter != end)
	{
		if (*iter == "#" || *iter == "[" || *iter == "]")
			break ;
		this->_text += *iter;
		iter++;
	}
	this->checkFragmentText();
}

Fragment::~Fragment(void)
{
}

void	Fragment::checkFragmentText(void)
{
	size_t	i = 0;

	while (i < this->_text.size())
	{
		if (this->_text[i] == '%' && !is_pct_encoded(this->_text.substr(i)))
			throw (std::invalid_argument("incorrect fragment"));
		else if (is_pct_encoded(this->_text.substr(i)))
			i += 3;
		else if (is_pchar(this->_text[i]))
			i++;
		else if (this->_text[i] == '/' || this->_text[i] == '?')
			i++;
		else
			throw (std::invalid_argument("incorrect fragment"));
	}
}

std::string	Fragment::getText(void) const 
{
	return (this->_text);
}

