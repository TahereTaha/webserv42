#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolServer.hpp>

#include <KeyWordServer.hpp>
#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>

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

AParser	*SymbolServer::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleSymbol(KeyWordServer().clone());
	return (new AParser(this->clone(), rule));
}



