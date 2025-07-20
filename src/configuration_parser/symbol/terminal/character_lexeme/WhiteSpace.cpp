#include <string>

#include <WhiteSpace.hpp>

WhiteSpace::WhiteSpace(void) : ATerminal()
{
}

WhiteSpace::~WhiteSpace(void)
{
}

ASymbol* WhiteSpace::clone() const
{
    return new WhiteSpace(*this);
}

size_t	 WhiteSpace::getTerminalSizeOnStr(const std::string& str) const 
{
	size_t	i = 0;
	char	*c_str = (char *) str.c_str();

	while (c_str[i] == ' ' || c_str[i] == '\t' || c_str[i] == '\r' || c_str[i] == '\n')
	{
		if (c_str[i] == '\r')
		{
			if (c_str[i + 1] != '\n')
				break ;
			i += 2;
		}
		else
			i++;
	}
	return (i);
}
