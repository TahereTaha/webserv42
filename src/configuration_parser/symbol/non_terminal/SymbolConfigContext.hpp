#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

#include <intermediate_representation.hpp>

class SymbolConfigContext : public ANonTerminal
{
	private:
		std::vector<t_server>	_servers;
	protected:
	public:
		SymbolConfigContext(void);
		~SymbolConfigContext(void);

		const char		*what(void) const;
		SymbolConfigContext	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
		std::vector<t_server>	getServers(void) const ;
};
