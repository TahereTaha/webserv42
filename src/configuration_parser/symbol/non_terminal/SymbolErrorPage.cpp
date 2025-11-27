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

#include <utils.hpp>
#include <Path.hpp>

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
	TextConfigFile	*text;
	if (self->getChildNodeSize() < 2)
		throw (std::invalid_argument("incorrect arrguments to error page."));
	text = dynamic_cast<TextConfigFile *>(self->getChildNode(self->getChildNodeSize() - 1)->getContent());
	if (!text)
		throw (std::invalid_argument("incorrect arrguments to error page."));
	Path	file_path(text->getText());
	size_t	i = 0;
	while (i < (self->getChildNodeSize() - 1))
	{
		Number	*number_token;
		number_token = dynamic_cast<Number *>(self->getChildNode(i)->getContent());
		if (!number_token)
			throw (std::invalid_argument("incorrect arrguments to error page."));
		t_status_code status_code = stricter_unsigned_stoi(number_token->getText(), (size_t *)std::string::npos);
		t_error_page error_page;
		error_page.uri = file_path.getPathText();
		error_page.status_code = status_code;
		this->_error_pages.push_back(error_page);
		i++;
	}
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

std::vector<t_error_page>	SymbolErrorPage::getErrorPages(void) const
{
	return (this->_error_pages);
}
