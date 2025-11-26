#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

#include <intermediate_representation.hpp>

class SymbolLimitExcept : public ANonTerminal
{
	private:
		std::vector<t_http_method>	_methods;
	protected:
	public:
		SymbolLimitExcept(void);
		~SymbolLimitExcept(void);

		const char			*what(void) const;
		SymbolLimitExcept	*clone(void) const;
		void				evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;

		std::vector<t_http_method>	getMethods(void) const ;
};
