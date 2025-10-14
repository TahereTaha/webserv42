#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolIndex : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolIndex(void);
		~SymbolIndex(void);

		const char		*what(void) const;
		SymbolIndex	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
