#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordReturn : public ATerminal
{
	private:
	protected:
	public:
		KeyWordReturn(void);
		virtual		ASymbol* clone() const;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
};

