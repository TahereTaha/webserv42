#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordErrorPage : public ATerminal
{
	private:
	protected:
	public:
		KeyWordErrorPage(void);
		virtual	ASymbol* clone() const;
		size_t	getTerminalSizeOnStr(const std::string & str) const;
};

