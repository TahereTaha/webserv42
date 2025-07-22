#include <stddef.h>

#include <string>
#include <cctype>
#include <cstdlib>

#include <Number.hpp>

Number::Number(void) : ATerminal()
{
}

Number::~Number(void)
{
}

ATerminal* Number::clone() const
{
	return new Number(*this);
}

size_t	Number::getTerminalSizeOnStr(const std::string & str) const 
{
	size_t	i = 0;
	char	*c_str = (char *) str.c_str();

	while (std::isdigit(c_str[i]))
	{
		i++;
	}
	return (i);
}

int		Number::getValue(void) const
{
	return (atoi(this->_text.c_str()));
}
