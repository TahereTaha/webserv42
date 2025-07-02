#pragma once

#include <string>
#include "Symbol.hpp"

class Terminal : public Symbol
{
	private:
	protected:
		std::string _text;
	public:
		Terminal(void);
		//	no need for a destructor here because this is abstract too.
};
