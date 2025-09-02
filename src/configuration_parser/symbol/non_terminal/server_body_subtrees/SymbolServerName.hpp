#pragma once

#include <vector>
#include <string>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolServerName : public ANonTerminal
{
	private:
		std::string _name;

		SymbolServerName(void);
		~SymbolServerName(void);
	protected:
	public:

		const char	*what(void) const;
		static Tree<ANonTerminal *>	*generateSubTree(terminal_iterator &iter, \
				const terminal_iterator &end);

		void	setName(std::string name);
		std::string	getName(void) const ;
};
