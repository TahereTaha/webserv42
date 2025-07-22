#pragma once

#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordAutoIndex : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordAutoIndex(void);
		~KeyWordAutoIndex(void);

		ATerminal*	clone(void) const;
};
