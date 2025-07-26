#pragma once

#include <AKeyWord.hpp>

class KeyWordClientMaxBodySize : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordClientMaxBodySize(void);
		~KeyWordClientMaxBodySize(void);

		const char	*what(void) const ;
		ATerminal*	clone(void) const;
};
