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

size_t	getTerminalSizeOnStr(const std::string & str)
{
	size_t					size = 0;
	size_t					i = 0;

	while (i < str.size() && isdigit(str[i]))
	{
		size++;
		it++;
	}
	return (size);
}
