#include <KeyPoint.hpp>

KeyPoint::KeyPoint(void) : ATerminal()
{
}

ATerminal* KeyPoint::clone() const
{
	return new KeyPoint(*this);
}

size_t	 KeyPoint::getTerminalSizeOnStr(const std::string& str)
{
	if (!str.empty() && str[0] == '.')
		return (1);
	return (0);
}
