#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolConfigContext : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolConfigContext(void);
		~SymbolConfigContext(void);

		const char		*what(void) const;
		SymbolConfigContext	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
