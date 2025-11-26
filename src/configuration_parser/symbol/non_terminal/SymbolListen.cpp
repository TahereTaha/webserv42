#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolListen.hpp>

#include <KeyWordListen.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolListen.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolListen::SymbolListen(void)
{
}

SymbolListen::~SymbolListen(void)
{
}

const char	*SymbolListen::what(void) const
{
	return ("listen_symbol");
}

SymbolListen	*SymbolListen::clone(void) const 
{
	return (new SymbolListen(*this));
}

void		SymbolListen::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolListen::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordListen().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleSymbol(TextConfigFile().clone())),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

