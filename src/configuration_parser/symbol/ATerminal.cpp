
#include <ATerminal.hpp>

ATerminal::ATerminal(void) : ASymbol()
{
	_text = "";
}

//
//ATerminal::ATerminal(const ATerminal & src) : ASymbol()
//{
//	*this = src;
//}
//
//ATerminal & operator = (const ATerminal & src)
//{
//	if (this == &src)
//		return (*this);
//	this->_text = src._text;
//	return (*this);
//}
//

static std::string	remove_quotes(std::string text)
{
	std::string	new_text = "";

	size_t	i = 0;
	while (i < text.size())
	{
		if (text[i] == '"')
			i++;
		else
		{
			new_text += text.substr(i, text.substr(i).find('"'));
			if (text.find('"') == std::string::npos)
				i = text.size();
			else
				i += text.substr(i).find('"');
		}
	}
	return (new_text);
}

void	ATerminal::setText(const std::string & text)
{
	this->_text = remove_quotes(text);
}

std::string	ATerminal::getText(void) const
{
	return (_text);
}

size_t		ATerminal::getTextLength(void) const
{
	return (_text.size());
}

//
//int get_match(const std::string &src, const std::string &pattern)
//{
//	int i = 0;
//	while (strchr(pattern.c_str(), src[i]) != nullptr && src[i] != '\0')
//		i++;
//	return (i);
//}
//
//std::string get_pattern(const std::string &src, const std::string &pattern)
//{
//	int i = get_match(src, pattern);
//	return (src.substr(0, i));
//}
