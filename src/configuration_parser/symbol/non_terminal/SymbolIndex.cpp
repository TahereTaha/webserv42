#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolIndex.hpp>

#include <KeyWordIndex.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolIndex.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

#include <string>
#include <vector>
#include <stdexcept>
#include <Path.hpp>

SymbolIndex::SymbolIndex(void)
{
}

SymbolIndex::~SymbolIndex(void)
{
}

const char	*SymbolIndex::what(void) const
{
	return ("index_symbol");
}

SymbolIndex	*SymbolIndex::clone(void) const 
{
	return (new SymbolIndex(*this));
}

void		SymbolIndex::evaluate(Tree<AEvaluable*> *self)
{
	TextConfigFile	*text;

	//	error checking.
	size_t	i = 0;
	while (i < self->getChildNodeSize())
	{
		text = dynamic_cast<TextConfigFile *>(self->getChildNode(i)->getContent());
		if (!text)
			throw (std::invalid_argument("incorrect arrguments to index."));
		Path file(text->getText());
		if (file.getSections().size() != 1)
			throw (std::invalid_argument("incorrect arrguments to index."));
		this->_indexFiles.push_back(file.getPathText());
		i++;
	}
}

AParser	*SymbolIndex::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordIndex().clone()),\
			new ParsingRuleRepetition(0, -1, new ParsingRuleSymbol(TextConfigFile().clone())),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

std::vector<std::string>	SymbolIndex::getIndexFiles(void) const 
{
	return (this->_indexFiles);
}

