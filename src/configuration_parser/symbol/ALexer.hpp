#pragma once

#include <Symbol.hpp>
#include <Terminal.hpp>

class TerminalFactory
{
	private:
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
