#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordServerName : public ATerminal
{
	private:
	protected:
	public:
		KeyWordServerName(void);
		virtual ASymbol* clone() const;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
};

