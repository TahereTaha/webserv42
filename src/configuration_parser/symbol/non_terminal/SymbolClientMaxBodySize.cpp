#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolClientMaxBodySize.hpp>

#include <KeyWordClientMaxBodySize.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolClientMaxBodySize::SymbolClientMaxBodySize(void)
{
}

SymbolClientMaxBodySize::~SymbolClientMaxBodySize(void)
{
}

const char	*SymbolClientMaxBodySize::what(void) const
{
	return ("client_max_body_size_symbol");
}

SymbolClientMaxBodySize	*SymbolClientMaxBodySize::clone(void) const 
{
	return (new SymbolClientMaxBodySize(*this));
}

void		SymbolClientMaxBodySize::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolClientMaxBodySize::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordClientMaxBodySize().clone()),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

