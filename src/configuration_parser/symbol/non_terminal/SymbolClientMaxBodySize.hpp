#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolClientMaxBodySize : public ANonTerminal
{
	private:
		size_t	_max_body_size;
	protected:
	public:
		SymbolClientMaxBodySize(void);
		~SymbolClientMaxBodySize(void);

		const char		*what(void) const;
		SymbolClientMaxBodySize	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;

		size_t	getMaxBodySize(void) const ;
};
