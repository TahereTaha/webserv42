#include <AParser.hpp>

AParser::AParser(void)
{
}

AParser::~AParser(void)
{
	size_t	i = 0;
	while (i < this->_symbols.size())
	{
		delete (this->_symbols[i]);
		i++;
	}
}

void	AParser::addSymbol(ASymbol *symbol)
{
	ASymbol	*new_symbol = symbol.clone();
	this->_symbols.push_back(new_symbol);
}

Tree<AEvaluable*>	*AParser::generateSubTree(terminal_iter &iter, const terminal_iter &iter &end)
{
	if ()
	size_t	i = 0;
	while (i < this->_symbols.size())
	{

		i++;
	}
}

