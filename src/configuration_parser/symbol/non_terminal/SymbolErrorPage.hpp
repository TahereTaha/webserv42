#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolErrorPage : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolErrorPage(void);
		~SymbolErrorPage(void);

		const char		*what(void) const;
		SymbolErrorPage	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
