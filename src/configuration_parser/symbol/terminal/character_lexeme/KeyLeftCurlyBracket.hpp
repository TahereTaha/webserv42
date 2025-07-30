#pragma once

#include <AKeyWord.hpp>

class KeyLeftCurlyBracket : public AKeyWord
{
	private:
	protected:
	public:
		KeyLeftCurlyBracket(void);
		~KeyLeftCurlyBracket(void);
		
		const char	*what(void) const ;
		ATerminal*	clone(void) const;
};
