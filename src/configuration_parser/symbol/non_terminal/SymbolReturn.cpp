#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolReturn.hpp>

#include <KeyWordReturn.hpp>
#include <Number.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolReturn.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

#include <stdexcept>
#include <utils.hpp>
#include <URI.hpp>

SymbolReturn::SymbolReturn(void)
{
}

SymbolReturn::~SymbolReturn(void)
{
}

const char	*SymbolReturn::what(void) const
{
	return ("return_symbol");
}

SymbolReturn	*SymbolReturn::clone(void) const 
{
	return (new SymbolReturn(*this));
}

#include <iostream>

void		SymbolReturn::evaluate(Tree<AEvaluable*> *self)
{
	Number			*status_code;
	TextConfigFile	*body_text;

	//	error checking.
	if (self->getChildNodeSize() < 1 || self->getChildNodeSize() > 2)
		throw (std::invalid_argument("incorrect arrguments to return."));
	if (self->getChildNodeSize() == 2 && !dynamic_cast<Number *>(self->getChildNode(0)->getContent()))
		throw (std::invalid_argument("incorrect arrguments to return."));
	if (self->getChildNodeSize() == 2 && !dynamic_cast<TextConfigFile *>(self->getChildNode(1)->getContent()))
		throw (std::invalid_argument("incorrect arrguments to return."));
	if (self->getChildNodeSize() == 1 && !dynamic_cast<TextConfigFile *>(self->getChildNode(0)->getContent()))
		throw (std::invalid_argument("incorrect arrguments to return."));

	//	seting some variables.
	if (self->getChildNodeSize() == 2)
	{
		status_code = dynamic_cast<Number *>(self->getChildNode(0)->getContent());
		body_text = dynamic_cast<TextConfigFile *>(self->getChildNode(1)->getContent());
	}
	else
	{
		status_code = NULL;
		body_text = dynamic_cast<TextConfigFile *>(self->getChildNode(0)->getContent());
	}

	// set the correct status code.
	if (status_code)
		this->_statusCode = stricter_unsigned_stoi(status_code->getText(), (size_t *)std::string::npos, 10);
	else
		this->_statusCode = 302;
	
	// set the content of the body.
	this->_bodyText = body_text->getText();
	if (this->_statusCode >= 300 && this->_statusCode < 400)
	{
		//	try to create a uri class to check that it is a correct uri.
		URI	url(this->_bodyText);
		(void)url;
	}
}

AParser	*SymbolReturn::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordReturn().clone()),\
			new ParsingRuleRepetition(0, 1, new ParsingRuleSymbol(Number().clone())),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

int			SymbolReturn::getStatusCode(void) const
{
	return (this->_statusCode);
}

std::string	SymbolReturn::getBodyText(void) const
{
	return (this->_bodyText);
}

