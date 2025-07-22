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

		ATerminal*	clone(void) const;
};
