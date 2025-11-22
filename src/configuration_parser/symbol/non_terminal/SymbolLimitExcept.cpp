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

#include <intermediate_representation.hpp>
#include <stdexcept>

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

static t_http_method	str_to_http_method(std::string text)
{
	if (text == "GET" || text == "get")
		return (GET);
	if (text == "POST" || text == "post")
		return (POST);
	if (text == "DELETE" || text == "delete")
		return (DELETE);
	return ((t_http_method)-1);
}

void		SymbolLimitExcept::evaluate(Tree<AEvaluable*> *self)
{
	TextConfigFile	*text;

	//	error checking.
	size_t	i = 0;
	while (i < self->getChildNodeSize())
	{
		text = dynamic_cast<TextConfigFile *>(self->getChildNode(i)->getContent());
		if (!text)
			throw (std::invalid_argument("incorrect arrguments to limitexcept."));
		t_http_method method = str_to_http_method(text->getText());
		if (method == -1)
			throw (std::invalid_argument("incorrect arrguments to limitexcept."));
		this->_methods.push_back(method);
		i++;
	}
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

std::vector<t_http_method>	SymbolLimitExcept::getMethods(void) const
{
	return (this->_methods);
}
