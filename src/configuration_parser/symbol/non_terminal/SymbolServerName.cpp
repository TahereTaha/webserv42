#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolServerName.hpp>

#include <KeyWordServerName.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolServerName::SymbolServerName(void)
{
}

SymbolServerName::~SymbolServerName(void)
{
}

const char	*SymbolServerName::what(void) const
{
	return ("server_name_symbol");
}

SymbolServerName	*SymbolServerName::clone(void) const 
{
	return (new SymbolServerName(*this));
}

void		SymbolServerName::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolServerName::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordServerName().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleSymbol(TextConfigFile().clone())),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

