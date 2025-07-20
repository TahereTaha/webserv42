#pragma once

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordRoot : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordRoot(void);
		~KeyWordRoot(void);

		ASymbol*	clone(void) const;
};
