#pragma once

#include <AKeyWord.hpp>

class KeySemicolon : public AKeyWord
{
	private:
	protected:
	public:
		KeySemicolon(void);
		~KeySemicolon(void);
		
		ASymbol*	clone(void) const;
};

