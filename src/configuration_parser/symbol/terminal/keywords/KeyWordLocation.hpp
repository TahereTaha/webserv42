#pragma once

#include <ATerminal.hpp>
#include <AKeyWord.hpp>

class KeyWordLocation : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordLocation(void);
		~KeyWordLocation(void);

		const char	*what(void) const ;
		ATerminal*	clone(void) const;
};
