#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolRoot.hpp>

#include <KeyWordRoot.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolRoot.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolRoot::SymbolRoot(void)
{
}

SymbolRoot::~SymbolRoot(void)
{
}

const char	*SymbolRoot::what(void) const
{
	return ("root_symbol");
}

SymbolRoot	*SymbolRoot::clone(void) const 
{
	return (new SymbolRoot(*this));
}

void		SymbolRoot::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolRoot::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordRoot().clone()),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

