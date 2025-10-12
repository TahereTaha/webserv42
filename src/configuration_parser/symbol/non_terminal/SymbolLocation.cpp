#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolLocation.hpp>

#include <KeyWordLocation.hpp>
#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>
#include <Number.hpp>
#include <TextConfigFile.hpp>

#include <SymbolLocation.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolLocation::SymbolLocation(void)
{
}

SymbolLocation::~SymbolLocation(void)
{
}

const char	*SymbolLocation::what(void) const
{
	return ("location_symbol");
}

SymbolLocation	*SymbolLocation::clone(void) const 
{
	return (new SymbolLocation(*this));
}

void		SymbolLocation::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolLocation::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordLocation().clone()),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeyLeftCurlyBracket().clone()),\
			new ParsingRuleRepetition(0, -1, new ParsingRuleOr(\
				new ParsingRuleSymbol(SymbolLocation().clone()),\
				NULL)),\
			new ParsingRuleSymbol(KeyRightCurlyBracket().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

