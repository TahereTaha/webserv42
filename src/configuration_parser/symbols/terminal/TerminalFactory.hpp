#pragma once

#include <Symbol.hpp>
#include <Terminal.hpp>
#include <vector>
#include <functional>

typedef std::function<Terminal*(std::string str)> TerminalConstructor;
class TerminalFactory
{
	private:
		TerminalFactory(void);
		TerminalFactory(const TerminalFactory & src);
		int AddNextSymbol(std::string content);
	protected:
		std::vector<Symbol *>	_tokenVector;
		std::vector<Terminal*>	_constructors;
	public:
		TerminalFactory(std::string content);
		virtual ~TerminalFactory() = 0;
};

