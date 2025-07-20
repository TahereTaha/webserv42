#pragma once

#include <ASymbol.hpp>
#include <ATeminal.hpp>
#include <AKeyWord.hpp>

class KeyWordLocation : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordLocation(void);
		~KeyWordLocation(void);

		ASymbol*	clone(void) const;
}
