#include <ParsingRuleSymbol.hpp>

ParsingRuleSymbol::ParsingRuleSymbol(const ASymbol *symbol)
{
	this->_symbol = symbol.clone();
}

ParsingRuleSymbol::~ParsingRuleSymbol(void)
{
	delete (this->_symbol);
}

