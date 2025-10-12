#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolLocation : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolLocation(void);
		~SymbolLocation(void);

		const char		*what(void) const;
		SymbolLocation	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
