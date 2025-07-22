#pragma once

#include <ATerminal.hpp>
#include <string>
#include <vector>

class ATerminalFactory
{
	private:
		size_t	_line;
		size_t	_column;
		std::vector<ATerminal *>	terminals;
	protected:
		void	addTerminalToFactory(ATerminal * terminal);
		
		void	updateIndex(const std::string & str);
		ATerminalFactory(void);
	public:
		~ATerminalFactory(void);

		ATerminal*	createTerminal(const std::string & str);

		void	resetIndex(void);
};

