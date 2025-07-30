#pragma once

#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordIndex : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordIndex(void);
		~KeyWordIndex(void);

		const char	*what(void) const ;
		ATerminal*	clone(void) const;
};
