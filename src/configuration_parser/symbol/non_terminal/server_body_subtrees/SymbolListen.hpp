#pragma once

class SymbolListen : public ANonTerminal
{
	private:
	protected:
	public:
		SymbolListen(void);
		~SymbolListen(void);

		const char	*what(void) const;
		static Tree<ANonTerminal *>	*generateSubTree(terminal_iterator &iter, \
				const terminal_iterator &end);
};
