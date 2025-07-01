#pragma once

#include <vector>

class Symbol
{
	private:
	protected:
	public:
		Symbol(void);
		virtual	Symbol(const Symbol & src);
		virtual	Symbol & operator = (const Symbol & src);
		virtual ~Symbol(void) = 0;
};

class TerminalFactory
{
	private:
	protected:
		std::vector<Symbol *>	_tokenVector;
	public:
		TerminalFactory(void);
		virtual	TerminalFactory(const TerminalFactory & src);
		virtual	TerminalFactory & operator = (const TerminalFactory & src);
		virtual ~TerminalFactory() = 0;
		add_token(ifstream str);
};
