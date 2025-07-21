#pragma once

#include <iostream>
#include <AKeyWord.hpp>

class KeyWordListen : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordListen(void);
		~KeyWordListen(void);
		
		ATerminal* clone() const;
};

