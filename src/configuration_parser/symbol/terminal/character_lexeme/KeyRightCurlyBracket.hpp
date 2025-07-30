#pragma once

#include <AKeyWord.hpp>

class KeyRightCurlyBracket : public AKeyWord
{
	private:
	protected:
	public:
		KeyRightCurlyBracket(void);
		~KeyRightCurlyBracket(void);

		const char	*what(void) const ;
		ATerminal*	clone(void) const;
};

