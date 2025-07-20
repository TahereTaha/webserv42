#pragma once

#include <ATerminal.hpp>

class WhiteSpace : public ATerminal
{
	private:
	protected:
	public:
		WhiteSpace(void);
		~WhiteSpace(void);
		
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ASymbol*	clone(void) const;
};
