#pragma once

#include <stirng>
#include <Symbol>

class Terminal : public Symbol
{
	private:
	protected:
		std::string _text;
	public:
		Terminal(void);
		//	no need for a destructor here because this is abstract too.
};
