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

		const char	*what(void) const;
		static Tree<ANonTerminal *>	*generateSubTree(terminal_iterator &iter, \
				const terminal_iterator &end);
};
