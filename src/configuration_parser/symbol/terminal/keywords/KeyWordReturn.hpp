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
		
		ATerminal* clone() const;
};

