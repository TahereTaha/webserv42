#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolReturn : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolReturn(void);
		~SymbolReturn(void);

		const char		*what(void) const;
		SymbolReturn	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
