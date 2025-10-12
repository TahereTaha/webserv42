#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolServerName : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolServerName(void);
		~SymbolServerName(void);

		const char		*what(void) const;
		SymbolServerName	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
