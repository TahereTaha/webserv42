#pragma once

#include "../Symbol.hpp"
#include "iostream"
#include "./TestFactory/TypeTerminalVector.hpp"

class TerminalFactory
{
	private:
		TerminalFactory(const TerminalFactory &src);
	protected:	
		int					getTokenMatch(std::string content);
		int 				getTokens(std::string content);
		TerminalVector		_tokenVector;
		TerminalVector		_constructors;
	public:
		TerminalFactory(void);
		virtual 			~TerminalFactory();
		void				printTokens();
};



