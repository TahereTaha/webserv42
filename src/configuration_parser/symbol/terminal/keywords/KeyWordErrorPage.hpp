#pragma once

#include <iostream>
#include <AKeyWord.hpp>

class KeyWordErrorPage : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordErrorPage(void);
		~KeyWordErrorPage(void);

		const char	*what(void) const ;
		ATerminal* clone() const;
};

