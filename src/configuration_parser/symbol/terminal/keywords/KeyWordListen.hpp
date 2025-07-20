#pragma once

#include <iostream>
#include <ATerminal.hpp>

class KeyWordListen : public ATerminal
{
	private:
	protected:
	public:
		KeyWordListen(void);
		virtual ASymbol* clone() const;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
};

