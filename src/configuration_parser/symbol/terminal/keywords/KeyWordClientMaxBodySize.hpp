#pragma once

#include <AKeyWord.hpp>

class KeyWordClientMaxBodySize : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordClientMaxBodySize(void);
		~KeyWordClientMaxBodySize(void);

		ATerminal*	clone(void) const;
};
