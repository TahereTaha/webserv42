#include <Path.hpp>

#include <cctype>

#include <URI.hpp>
#include <percent_encoding_utils.hpp>
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

Path::Path(void)
{
}

Path::Path(std::string text)
{
	this->_text = text;
	this->check_correct_path();
}

Path::Path(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end)
{
	this->_text = "";
	while (iter != end && *iter != "?" && *iter != "#")
	{
		this->_text += *iter;
		iter++;
	}
	this->check_correct_path();
}

Path::~Path(void)
{
}

void	Path::check_correct_path(void)
{
	size_t	i = 0;

	while (i < this->_text.size())
	{
		if (is_pct_encoded(this->_text.substr(i)))
			i += 3;
		else if (is_pchar(this->_text[i]))
			i++;
		else if (this->_text[i] == '/')
			i++;
		else
			throw (std::invalid_argument("incorrect path"));
	}
}

