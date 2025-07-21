#pragma once

#include <AKeyWord.hpp>

class KeyLeftCurlyBracket : public AKeyWord
{
	private:
	protected:
	public:
		KeyLeftCurlyBracket(void);
		~KeyLeftCurlyBracket(void);
		
		ASymbol*	clone(void) const;
};
