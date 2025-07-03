
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

void	ATerminal::setText(const std::string & text)
{
	_text = text;
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
