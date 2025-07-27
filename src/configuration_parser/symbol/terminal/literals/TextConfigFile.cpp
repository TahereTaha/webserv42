#include <stddef.h>

#include <string>
#include <cctype>
#include <cstdlib>

#include <TextConfigFile.hpp>

TextConfigFile::TextConfigFile(void) : ATerminal()
{
}

TextConfigFile::~TextConfigFile(void)
{
}

ATerminal* TextConfigFile::clone() const
{
	return new TextConfigFile(*this);
}

//	safe characters that arent used in control or as separators.
static int	is_safe(int ch)
{
	if (!std::isprint(ch))
		return (0);
	if (ch == ' ' || ch == '{' || ch == '}' || ch == ';' || ch == '"')
		return (0);
	return (1);
}

static size_t	get_quoted_section_len(char *str)
{
	size_t	i = 0;

	if (str[i] == '"')
		i++;
	else
		return (0);
	while (str[i] >= ' ' && str[i] <= '~' && str[i] != '"')
	{
		i++;
	}
	if (str[i] == '"')
		i++;
	else
		return (0);
	return (i);
}

size_t	TextConfigFile::getTerminalSizeOnStr(const std::string & str) const  
{
	size_t	i = 0;
	size_t	quoted_section_len = 0;
	char	*c_str = (char *) str.c_str();

	while (is_safe(c_str[i]) || c_str[i] == '"')
	{
		quoted_section_len = get_quoted_section_len(c_str);
		if (c_str[i] == '"' && quoted_section_len == 0)
			break ;
		if (quoted_section_len != 0)
			i += quoted_section_len;
		else
			i++;
	}
	return (i);
}

std::string		TextConfigFile::getValue(void) const
{
	return (this->_text);
}

const char	*TextConfigFile::what(void) const 
{
	return ("text");
}
