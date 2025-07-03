#pragma once

#include <ATerminal.hpp>

class KeySemicolon : public ATerminal
{
	private:
	protected:
	public:
		KeySemicolon(void);
//		KeySemicolon(const KeySemicolon & src);
//		KeySemicolon & operator = (const KeySemicolon & src); // maybe no need to redefine it.
		~KeySemicolon(void);
		
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;
};

