#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolLimitExcept.hpp>

#include <KeyWordLimitExept.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolLimitExcept.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolLimitExcept::SymbolLimitExcept(void)
{

}

SymbolLimitExcept::~SymbolLimitExcept(void)
{
}

const char	*SymbolLimitExcept::what(void) const
{
	return ("limit_except_symbol");
}

SymbolLimitExcept	*SymbolLimitExcept::clone(void) const 
{
	return (new SymbolLimitExcept(*this));
}

void		SymbolLimitExcept::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolLimitExcept::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordLimitExept().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleSymbol(TextConfigFile().clone())),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

