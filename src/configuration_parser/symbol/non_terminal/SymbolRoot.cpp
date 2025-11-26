#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolRoot.hpp>

#include <KeyWordRoot.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolRoot.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

#include <stdexcept>
#include <Path.hpp>

SymbolRoot::SymbolRoot(void)
{
}

SymbolRoot::~SymbolRoot(void)
{
}

const char	*SymbolRoot::what(void) const
{
	return ("root_symbol");
}

SymbolRoot	*SymbolRoot::clone(void) const 
{
	return (new SymbolRoot(*this));
}

void		SymbolRoot::evaluate(Tree<AEvaluable*> *self)
{
	TextConfigFile	*root_path_text;

	//	error checking.
	if (self->getChildNodeSize() != 1)
		throw (std::invalid_argument("incorrect arrguments to root."));
	if (!dynamic_cast<TextConfigFile *>(self->getChildNode(0)->getContent()))
		throw (std::invalid_argument("incorrect arrguments to root."));

	root_path_text = dynamic_cast<TextConfigFile *>(self->getChildNode(0)->getContent());

	Path	root_path(root_path_text->getText());
	this->_path = root_path.getPathText();
}

AParser	*SymbolRoot::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordRoot().clone()),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

std::string	SymbolRoot::getPath(void) const
{
	return (this->_path);
}

