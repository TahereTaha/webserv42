#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolConfigContext.hpp>

#include <SymbolServer.hpp>


#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolConfigContext::SymbolConfigContext(void)
{
}

SymbolConfigContext::~SymbolConfigContext(void)
{
}

const char	*SymbolConfigContext::what(void) const
{
	return ("configuration context");
}

SymbolConfigContext	*SymbolConfigContext::clone(void) const 
{
	return (new SymbolConfigContext(*this));
}

void		SymbolConfigContext::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolConfigContext::getParser(void) const
{
	AParsingRule	*rule = new ParsingRuleRepetition(1, -1, \
			new ParsingRuleSymbol(SymbolServer().clone()));
	return (new AParser(this->clone(), rule));
}

