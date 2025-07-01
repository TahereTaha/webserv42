#pragma once

#include <iostream>
#include "Terminal.hpp"

class Number : public Terminal
{
	private:
	protected:
	public:
		Number(void);
		Number(std::string str);
};

//do we add copy constructor and assign operator ??
