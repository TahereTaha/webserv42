#pragma once

#include <ATerminal.hpp>

class KeyLeftCurlyBracket : public ATerminal
{
	private:
	protected:
	public:
		KeyLeftCurlyBracket(void);
		~KeyLeftCurlyBracket(void);
		
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ASymbol*	clone(void) const;
};
