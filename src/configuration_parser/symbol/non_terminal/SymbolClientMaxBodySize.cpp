#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolClientMaxBodySize.hpp>

#include <KeyWordClientMaxBodySize.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

#include <utils.hpp>

SymbolClientMaxBodySize::SymbolClientMaxBodySize(void)
{
}

SymbolClientMaxBodySize::~SymbolClientMaxBodySize(void)
{
}

const char	*SymbolClientMaxBodySize::what(void) const
{
	return ("client_max_body_size_symbol");
}

SymbolClientMaxBodySize	*SymbolClientMaxBodySize::clone(void) const 
{
	return (new SymbolClientMaxBodySize(*this));
}

static size_t	get_file_size_unit(std::string unit_str)
{
	if (unit_str == "")
		return (1);
	if (unit_str == "KiB")
		return (1024);
	if (unit_str == "MiB")
		return (1048576);
	if (unit_str == "GiB")
		return (1073741824);
	return (0);
}

static size_t	parse_file_size(std::string file_size_str)
{
	size_t	i = 0;
	size_t	body_size = stoi(file_size_str, &i);
	body_size = body_size * get_file_size_unit(file_size_str.substr(i));
	return (body_size);
}

void		SymbolClientMaxBodySize::evaluate(Tree<AEvaluable*> *self)
{
	if (self->getChildNodeSize() != 1)
		throw (std::invalid_argument("incorrect arrguments to client max body size."));
	TextConfigFile	*text = dynamic_cast<TextConfigFile *>(self->getChildNode(0)->getContent());
	if (!text)
		throw (std::invalid_argument("incorrect arrguments to client max body size."));
	this->_max_body_size = parse_file_size(text->getText());
	if (this->_max_body_size == 0)
		throw (std::invalid_argument("incorect file size unit."));
}

AParser	*SymbolClientMaxBodySize::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordClientMaxBodySize().clone()),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

size_t	SymbolClientMaxBodySize::getMaxBodySize(void) const 
{
	return (this->_max_body_size);
}

