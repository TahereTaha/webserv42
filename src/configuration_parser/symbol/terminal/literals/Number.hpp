#pragma once

#include <iostream>
#include "ATerminal.hpp"

class Number : public ATerminal
{
	private:
	protected:
	public:
		Number();
		Number(std::string str);
		Number(const Number& other);
		Number& operator=(const Number& other);
		virtual Symbol* clone() const;
		size_t		getTerminalSizeOnStr(const std::string & str) const;	
};
