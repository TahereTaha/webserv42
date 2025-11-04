#include <Path.hpp>

#include <cctype>

#include <URI.hpp>
#include <percent_encoding_utils.hpp>
#include <tokenize.hpp>

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
	this->normalize_path();
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
	this->normalize_path();
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

void	Path::fill_sections(void)
{
	size_t	i = 0;
	std::vector<std::string>	dirty_sections = tokenize(this->_text, "/");

	while (i < dirty_sections.size())
	{
		if (dirty_sections[i] != "/")
			this->_sections.push_back(dirty_sections[i]);
		i++;
	}
}


void	Path::normalize_path(void)
{
	//	simplify all the . and ..
	{
		size_t	i = 0;
		std::vector<std::string>	new_sections;

		while (i < this->_sections.size())
		{
			if (new_sections.size() > 0 && this->_sections[i] == "..")
				new_sections.pop_back();
			else if (this->_sections[i] != ".")
				new_sections.push_back(this->_sections[i]);
			i++;
		}
		this->_sections = new_sections;
	}
	//	pct decoding.
	{
		size_t	i = 0;

		while (i < this->_sections.size())
		{
			this->_sections[i] = decode_pct_encoded_string(this->_sections[i]);
			i++;
		}
	}
}

