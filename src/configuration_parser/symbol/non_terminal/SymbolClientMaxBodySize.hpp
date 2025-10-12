#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolClientMaxBodySize : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolClientMaxBodySize(void);
		~SymbolClientMaxBodySize(void);

		const char		*what(void) const;
		SymbolClientMaxBodySize	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
