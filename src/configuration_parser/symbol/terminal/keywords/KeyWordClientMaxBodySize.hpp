#pragma once

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordClientMaxBodySize : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordClientMaxBodySize(void);
		~KeyWordClientMaxBodySize(void);

		ASymbol*	clone(void) const;
};
