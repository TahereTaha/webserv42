#pragma once

#include <vector>
#include <Tree.hpp>
#include <ASymbol.hpp>
#include <AEvaluable.hpp>

typedef std::vector<ATerminal*>::iterator terminal_iter;

class AParser
{
	private:
		//	codify the information about and, or, repetition, symple symbol.
		std::vector<ASymbol*>	_symbols;

		AParser(void);

		void	addSymbol(ASymbol *symbol);
	protected:
	public:
		~AParser(void);

		Tree<AEvaluable*>	*generateSubTree(terminal_iter &iter, const terminal_iter &end);

		friend class ANonTerminal;
};

