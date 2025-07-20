#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordServer : public ATerminal
{
	private:
	protected:
	public:
		KeyWordServer(void);
		virtual ASymbol* clone() const;
		size_t	getTerminalSizeOnStr(const std::string & str) const;
};

