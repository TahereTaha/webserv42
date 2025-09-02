#include <subTreeGenerationUtils.hpp>

#include <KeyRightCurlyBracket.hpp>
#include <KeyWordServer.hpp>
#include <KeyWordServerName.hpp>
#include <KeyWordListen.hpp>
#include <KeyWordClientMaxBodySize.hpp>
#include <KeyWordErrorPage.hpp>
#include <KeyWordLocation.hpp>
#include <KeyWordReturn.hpp>
#include <KeyWordRoot.hpp>
#include <KeyWordAutoIndex.hpp>
#include <KeyWordIndex.hpp>
#include <KeyWordLimitExept.hpp>

#include <SymbolServerName.hpp>

int	isSymbolInServerBody(ATerminal *symbol)
{
	if (dynamic_cast<KeyWordServerName*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordListen*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordClientMaxBodySize*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordErrorPage*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordLocation*>(symbol) != NULL)
		return (1);
	else
		return (0);
}

int	isSymbolInLocationBody(ATerminal *symbol)
{
	if (dynamic_cast<KeyWordLocation*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordReturn*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordRoot*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordAutoIndex*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordIndex*>(symbol) != NULL)
		return (1);
	if (dynamic_cast<KeyWordLimitExept*>(symbol) != NULL)
		return (1);
	else
		return (0);
}

//	if the symbol is server or the end. just return.
//	if the symbol is in the location body. trow a exeption.

Tree<ANonTerminal*>	*generateServerBodySubTree(terminal_iterator &iter, \
		const terminal_iterator & end)
{
	Tree<ANonTerminal*>	*subTree;

	if (iter == end)
		return (NULL);
	if (dynamic_cast<KeyWordServer*>(*iter) != NULL)
		return (NULL);
	if (dynamic_cast<KeyRightCurlyBracket*>(*iter) != NULL)
		return (NULL);
	else if (!isSymbolInServerBody(*iter))
	{
		parse_exception	e(UNRECOGNIZED_SYMBOL);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		throw (e);
	}

	if (dynamic_cast<KeyWordServerName*>(*iter) != NULL)
		subTree = SymbolServerName::generateSubTree(iter, end);
	else	// temporal. place holder of the other server directives.
	{
		parse_exception	e(UNDEFINED_ERROR);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		throw (e);
	}

	return (subTree);
}

