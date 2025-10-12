#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolListen : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolListen(void);
		~SymbolListen(void);

		const char		*what(void) const;
		SymbolListen	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
