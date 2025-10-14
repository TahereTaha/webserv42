#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolAutoIndex : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolAutoIndex(void);
		~SymbolAutoIndex(void);

		const char		*what(void) const;
		SymbolAutoIndex	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
