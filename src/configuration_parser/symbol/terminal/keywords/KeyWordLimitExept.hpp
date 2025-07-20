#pragma once

#include <ASymbol.hpp>
#include <ATeminal.hpp>
#include <AKeyWord.hpp>

class KeyWordLimitExept : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordLimitExept(void);
		~KeyWordLimitExept(void);

		ASymbol*	clone(void) const;
}
