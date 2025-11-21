#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolAutoIndex.hpp>

#include <KeyWordAutoIndex.hpp>
#include <Number.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolAutoIndex.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

#include <stdexcept>

SymbolAutoIndex::SymbolAutoIndex(void)
{
}

SymbolAutoIndex::~SymbolAutoIndex(void)
{
}

const char	*SymbolAutoIndex::what(void) const
{
	return ("auto_index_symbol");
}

SymbolAutoIndex	*SymbolAutoIndex::clone(void) const 
{
	return (new SymbolAutoIndex(*this));
}

void		SymbolAutoIndex::evaluate(Tree<AEvaluable*> *self)
{
	TextConfigFile	*value;
	this->_isSet = 0;

	//	error checking.
	if (self->getChildNodeSize() != 1)
		throw (std::invalid_argument("incorrect arrguments to autoindex."));
	if (!dynamic_cast<TextConfigFile *>(self->getChildNode(0)->getContent()))
		throw (std::invalid_argument("incorrect arrguments to autoindex."));

	value = dynamic_cast<TextConfigFile *>(self->getChildNode(0)->getContent());
	if (value->getText() == "on")
		this->_isSet = 1;
	else if (value->getText() == "off")
		this->_isSet = 0;
	else
		throw (std::invalid_argument("incorrect arrguments to autoindex."));
}

AParser	*SymbolAutoIndex::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordAutoIndex().clone()),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

int		SymbolAutoIndex::getIsSet(void) const
{
	return (this->_isSet);
}

