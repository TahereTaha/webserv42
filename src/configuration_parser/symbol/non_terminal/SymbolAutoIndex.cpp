#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolAutoIndex.hpp>

#include <KeyWordAutoIndex.hpp>
#include <Number.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolAutoIndex.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolAutoIndex::SymbolAutoIndex(void)
{
}

SymbolAutoIndex::~SymbolAutoIndex(void)
{
}

const char	*SymbolAutoIndex::what(void) const
{
	return ("auto_index_symbol");
}

SymbolAutoIndex	*SymbolAutoIndex::clone(void) const 
{
	return (new SymbolAutoIndex(*this));
}

void		SymbolAutoIndex::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolAutoIndex::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordAutoIndex().clone()),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

