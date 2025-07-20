#pragma once

#include <ASymbol.hpp>
#include <ATeminal.hpp>
#include <AKeyWord.hpp>

class KeyWordAutoIndex : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordAutoIndex(void);
		~KeyWordAutoIndex(void);

		ASymbol*	clone(void) const;
}
