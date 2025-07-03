#pragma once

#include <stddef.h>

#include <iostream>

#include <ATerminal.hpp>

class Number : public ATerminal
{
	private:
	protected:
	public:
		Number(void);
		Number(const Number & src);
		Number & operator = (const Number & src); // maybe no need to redefine it.
		~Number(void);
		
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;
};
