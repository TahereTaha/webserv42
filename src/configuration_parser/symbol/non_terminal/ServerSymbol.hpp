#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class ServerSymbol : public ANonTerminal
{
	private:
	protected:
	public:
		ServerSymbol(void);
		~ServerSymbol(void);

		const char	*what(void) const;
		static Tree<ANonTerminal *>	*generateSubTree(terminal_iterator &iter, \
				const terminal_iterator &end);
};
