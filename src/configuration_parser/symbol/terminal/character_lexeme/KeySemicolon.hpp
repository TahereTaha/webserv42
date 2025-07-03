#pragma once

#include <ATerminal.hpp>

class KeySemicolon : public ATerminal
{
	private:
	protected:
	public:
		KeySemicolon(void);
		~KeySemicolon(void);
		
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;
};

