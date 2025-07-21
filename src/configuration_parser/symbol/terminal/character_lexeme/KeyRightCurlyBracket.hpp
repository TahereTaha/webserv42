#pragma once

#include <AKeyWord.hpp>

class KeyRightCurlyBracket : public AKeyWord
{
	private:
	protected:
	public:
		KeyRightCurlyBracket(void);
		~KeyRightCurlyBracket(void);

		ATerminal*	clone(void) const;
};

