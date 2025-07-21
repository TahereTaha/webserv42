#pragma once

#include <vector>

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <ATerminalFactory.hpp>

class ALexer
{
	private:
	protected:
		ATerminalFactory*	_factory;
		ALexer(void);
	public:
		~ALexer(void);

		std::vector<ATerminal*>	tokenizeStr(const std::string & str) const ;
};
