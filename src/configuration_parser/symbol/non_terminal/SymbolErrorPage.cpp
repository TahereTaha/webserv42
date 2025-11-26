#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolErrorPage.hpp>

#include <KeyWordErrorPage.hpp>
#include <Number.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolErrorPage::SymbolErrorPage(void)
{
}

SymbolErrorPage::~SymbolErrorPage(void)
{
}

const char	*SymbolErrorPage::what(void) const
{
	return ("error_page_symbol");
}

SymbolErrorPage	*SymbolErrorPage::clone(void) const 
{
	return (new SymbolErrorPage(*this));
}

void		SymbolErrorPage::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

AParser	*SymbolErrorPage::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordErrorPage().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleSymbol(Number().clone())),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

