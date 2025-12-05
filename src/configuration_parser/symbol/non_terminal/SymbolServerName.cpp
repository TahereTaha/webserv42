#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolServerName.hpp>

#include <KeyWordServerName.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolServerName::SymbolServerName(void)
{
}

SymbolServerName::~SymbolServerName(void)
{
}

const char	*SymbolServerName::what(void) const
{
	return ("server_name_symbol");
}

SymbolServerName	*SymbolServerName::clone(void) const 
{
	return (new SymbolServerName(*this));
}

void		SymbolServerName::evaluate(Tree<AEvaluable*> *self)
{
	TextConfigFile	*text;

	size_t	i = 0;
	while (i < self->getChildNodeSize())
	{
		text = dynamic_cast<TextConfigFile *>(self->getChildNode(i)->getContent());
		if (!text)
			throw (std::invalid_argument("incorrect arrguments to limitexcept."));
		this->_names.push_back(text->getText());
		i++;
	}
}

AParser	*SymbolServerName::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordServerName().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleSymbol(TextConfigFile().clone())),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

std::vector<std::string>	SymbolServerName::getNames(void) const
{
	return (this->_names);
}
