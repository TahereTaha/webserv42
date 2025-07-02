#pragma once

#include <vector>
#include <string>
#include <iostream>

class Symbol
{
	private:
		Symbol(void);
	protected:
	public:
		virtual ~Symbol(void) = 0;
		Symbol(void) {};
		// Symbol(const Symbol & src);
		// virtual	Symbol & operator = (const Symbol & src);
};

