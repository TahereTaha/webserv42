#pragma once

#include <AKeyWord.hpp>

class KeySemicolon : public AKeyWord
{
	private:
	protected:
	public:
		KeySemicolon(void);
		~KeySemicolon(void);
		
		const char	*what(void) const ;
		ATerminal*	clone(void) const;
};

