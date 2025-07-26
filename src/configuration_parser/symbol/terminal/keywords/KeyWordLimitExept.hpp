#pragma once

#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordLimitExept : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordLimitExept(void);
		~KeyWordLimitExept(void);

		const char	*what(void) const ;
		ATerminal*	clone(void) const;
};
