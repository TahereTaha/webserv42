#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolRoot : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolRoot(void);
		~SymbolRoot(void);

		const char		*what(void) const;
		SymbolRoot	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
