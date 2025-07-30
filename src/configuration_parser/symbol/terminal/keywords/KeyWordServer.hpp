#pragma once

#include <iostream>
#include <AKeyWord.hpp>

class KeyWordServer : public AKeyWord
{
	private:
	protected:
	public:
		KeyWordServer(void);
		~KeyWordServer(void);
		
		const char	*what(void) const ;
		ATerminal* clone() const;
};

