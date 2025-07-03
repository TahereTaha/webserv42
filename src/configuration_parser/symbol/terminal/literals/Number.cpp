#include <stddef.h>

#include <string>
#include <cctype>

#include <Number.hpp>

Number::Number(void) : ATerminal()
{
}

//
//Number::Number(const Number & src) : ATerminal(src)
//{
//}
//

Number::~Number(void)
{
}

Symbol* Number::clone() const
{
	return new Number(*this);
}

size_t	Number::getTerminalSizeOnStr(const std::string & str)
{
	size_t					size = 0;
	std::string::iterator	it = str.begin();

	while (it != str.end() && isdigit(*it))
	{
		size++;
		it++;
	}
	return (size);
}
