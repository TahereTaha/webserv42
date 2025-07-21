#pragma once

#include <iostream>
#include <AKeyWord.hpp>

class KeyWordServerName : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordServerName(void);
		~KeyWordServerName(void);
		

		ATerminal* clone() const;
};

