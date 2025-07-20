#pragma once

#include <ATerminal.hpp>

class KeyRightCurlyBracket : public ATerminal
{
	private:
	protected:
	public:
		KeyRightCurlyBracket(void);
		~KeyRightCurlyBracket(void);

		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ASymbol*	clone(void) const;
};

