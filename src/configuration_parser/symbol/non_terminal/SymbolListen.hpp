#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

#include <intermediate_representation.hpp>

class SymbolListen : public ANonTerminal
{
	private:
		std::vector<struct sockaddr_storage>	_sockets;
	protected:
	public:
		SymbolListen(void);
		~SymbolListen(void);

		const char		*what(void) const;
		SymbolListen	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;

		std::vector<struct sockaddr_storage>	getSockets(void) const ;
};
