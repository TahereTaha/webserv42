#include "Number.hpp"
#include <cctype>

Number::Number(std::string str)
{
	int i = 0;

	std::string::iterator it = str.begin();
	
	while (it != str.end() && isdigit(*it))
	{
		i++;
		it++;
	}
	this->_text = str.substr(0, i);
}
