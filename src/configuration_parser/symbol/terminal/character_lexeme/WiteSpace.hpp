#pragma once

#include "Terminal.hpp"

class WiteSpace : public Terminal
{
	private:
		WiteSpace(void);
	protected:
	public:
		WiteSpace(std::string str);
};



WiteSpace::WiteSpace(std::string str)
{
	int i = 0;

	std::string::itrerator	it = str.begin();
	while (strchr("\n\t \r", *it))
	{
		i++;
		it++;
	}
	this->_text = str.substr(0, i);
}

