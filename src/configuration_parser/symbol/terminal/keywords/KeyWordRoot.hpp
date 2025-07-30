#pragma once

#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordRoot : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordRoot(void);
		~KeyWordRoot(void);

		const char	*what(void) const ;
		ATerminal*	clone(void) const;
};
