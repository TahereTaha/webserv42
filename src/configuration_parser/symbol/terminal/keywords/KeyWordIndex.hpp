#pragma once

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordIndex : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordIndex(void);
		~KeyWordIndex(void);

		ASymbol*	clone(void) const;
};
