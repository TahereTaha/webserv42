#pragma once

#include "../Symbol.hpp"
#include "Terminal.hpp"
#include <vector>
#include "iostream"

class TerminalFactory
{
	private:
		TerminalFactory(const TerminalFactory & src);
		int		AddNextSymbol(std::string content);
		void	SymbolReplaceLast(Terminal *symbol);
	protected:
		std::vector<Symbol *>	_tokenVector;
		std::vector<Terminal*>	_constructors;
	public:
		TerminalFactory(void);
		int Lexer(std::string content);
		virtual ~TerminalFactory() = 0;
		std::vector<Symbol *> getContent() const { return _tokenVector; }
};

std::ostream& operator<<(std::ostream& os, const TerminalFactory& tf) {
    std::vector<Symbol*> content = tf.getContent();

    for (Symbol* symbol : content) {
        if (Terminal* terminal = dynamic_cast<Terminal*>(symbol))
            os << terminal->getText() << " ";
    }
    return os;
}
