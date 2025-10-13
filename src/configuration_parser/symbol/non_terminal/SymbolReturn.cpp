#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolReturn.hpp>

#include <KeyWordReturn.hpp>
#include <Number.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolReturn.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolReturn::SymbolReturn(void)
{
}

SymbolReturn::~SymbolReturn(void)
{
}

const char	*SymbolReturn::what(void) const
{
	return ("return_symbol");
}

SymbolReturn	*SymbolReturn::clone(void) const 
{
	return (new SymbolReturn(*this));
}

void		SymbolReturn::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolReturn::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordReturn().clone()),\
			new ParsingRuleRepetition(0, 1, new ParsingRuleSymbol(Number().clone())),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

