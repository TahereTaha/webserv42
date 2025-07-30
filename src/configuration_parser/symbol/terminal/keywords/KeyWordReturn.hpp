#pragma once

#include <iostream>
#include <AKeyWord.hpp>

class KeyWordReturn : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordReturn(void);
		~KeyWordReturn(void);
		
		const char	*what(void) const ;
		ATerminal* clone() const;
};

