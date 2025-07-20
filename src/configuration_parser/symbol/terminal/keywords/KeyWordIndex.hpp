#pragma once

#include <ASymbol.hpp>
#include <ATeminal.hpp>
#include <AKeyWord.hpp>

class KeyWordIndex : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordIndex(void);
		~KeyWordIndex(void);

		ASymbol*	clone(void) const;
}
