#pragma once

#include <Tree.hpp>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

int	isSymbolInServerBody(ATerminal *symbol);
int	isSymbolInLocationBody(ATerminal *symbol);

Tree<ANonTerminal*>	*generateServerBodySubTree(terminal_iterator &iter, \
		const terminal_iterator & end);
Tree<ANonTerminal*>	*generateLocationBodySubTree(terminal_iterator &iter, \
		const terminal_iterator & end);

