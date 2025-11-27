#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

#include <intermediate_representation.hpp>

class SymbolErrorPage : public ANonTerminal
{
	private:
		std::vector<t_error_page>	_error_pages;
	protected:
	public:
		SymbolErrorPage(void);
		~SymbolErrorPage(void);

		const char		*what(void) const;
		SymbolErrorPage	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
		std::vector<t_error_page>	getErrorPages(void) const ;
};
