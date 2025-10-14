#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolIndex.hpp>

#include <KeyWordIndex.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolIndex.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolIndex::SymbolIndex(void)
{
}

SymbolIndex::~SymbolIndex(void)
{
}

const char	*SymbolIndex::what(void) const
{
	return ("index_symbol");
}

SymbolIndex	*SymbolIndex::clone(void) const 
{
	return (new SymbolIndex(*this));
}

void		SymbolIndex::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolIndex::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordIndex().clone()),\
			new ParsingRuleRepetition(0, -1, new ParsingRuleSymbol(TextConfigFile().clone())),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

