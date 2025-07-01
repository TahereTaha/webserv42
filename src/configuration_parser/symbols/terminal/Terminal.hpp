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
		virtual	Terminal(const Terminal & src);
		virtual	Terminal & operator = (const Terminal & src);
		//	no need for a destructor here because this is abstract too.
};
