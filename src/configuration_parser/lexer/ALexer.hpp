#pragma once

#include <vector>

#include <ASymbol.hpp>
#include <ATerminalFactory.hpp>

class ALexer
{
	private:
	protected:
		ATerminalFactory*	_factory;
		ALexer(void);
	public:
		~ALexer(void);

		std::vector<ASymbol*>	tokenizeStr(const std::string & str) const ;
};
