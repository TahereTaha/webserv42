#pragma once

#include <ASymbol.hpp>
#include <ATeminal.hpp>
#include <AKeyWord.hpp>

class KeyWordRoot : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordRoot(void);
		~KeyWordRoot(void);

		ASymbol*	clone(void) const;
}
