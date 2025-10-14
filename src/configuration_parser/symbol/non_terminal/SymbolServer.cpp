#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolServer.hpp>

#include <KeyWordServer.hpp>
#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>
#include <Number.hpp>

#include <SymbolServerName.hpp>
#include <SymbolListen.hpp>
#include <SymbolClientMaxBodySize.hpp>
#include <SymbolErrorPage.hpp>
#include <SymbolLocation.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolServer::SymbolServer(void)
{
}

SymbolServer::~SymbolServer(void)
{
}

const char	*SymbolServer::what(void) const
{
	return ("server_symbol");
}

SymbolServer	*SymbolServer::clone(void) const 
{
	return (new SymbolServer(*this));
}

void		SymbolServer::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolServer::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordServer().clone()),\
			new ParsingRuleSymbol(KeyLeftCurlyBracket().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleOr(\
				new ParsingRuleSymbol(SymbolServerName().clone()),\
				new ParsingRuleSymbol(SymbolListen().clone()),\
				new ParsingRuleSymbol(SymbolClientMaxBodySize().clone()),\
				new ParsingRuleSymbol(SymbolErrorPage().clone()),\
				new ParsingRuleSymbol(SymbolLocation().clone()),\
				NULL)),\
			new ParsingRuleSymbol(KeyRightCurlyBracket().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

