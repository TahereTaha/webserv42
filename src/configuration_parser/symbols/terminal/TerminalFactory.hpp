#pragma once

#include <Symbol.hpp>
#include <Terminal.hpp>

class TerminalFactory
{
	private:
		TerminalFactory(void);
	protected:
		std::vector<Symbol *>	_tokenVector;
	public:
		virtual ~TerminalFactory() = 0;
};
