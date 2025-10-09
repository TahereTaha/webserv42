#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolServer : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolServer(void);
		~SymbolServer(void);

		const char		*what(void) const;
		SymbolServer	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
};
