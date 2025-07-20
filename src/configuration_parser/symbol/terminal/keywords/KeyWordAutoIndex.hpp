#pragma once

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordAutoIndex : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordAutoIndex(void);
		~KeyWordAutoIndex(void);

		ASymbol*	clone(void) const;
};
