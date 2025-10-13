#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolLimitExcept : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolLimitExcept(void);
		~SymbolLimitExcept(void);

		const char			*what(void) const;
		SymbolLimitExcept	*clone(void) const;
		void				evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
