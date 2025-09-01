
#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <ServerSymbol.hpp>

#include <KeyWordServer.hpp>
#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>

ServerSymbol::ServerSymbol(void)
{
}

ServerSymbol::~ServerSymbol(void)
{
}

const char	*ServerSymbol::what(void) const
{
	return ("server_symbol");
}

Tree<ANonTerminal*>		*ServerSymbol::generateSubTree(terminal_iterator &iter, \
				const terminal_iterator &end)
{
	std::vector<ATerminal*>::iterator start = iter;

	//	check that it starts with a server keyword.
	if (iter == end || dynamic_cast<KeyWordServer*>(*iter) == NULL)
	{
		parse_exception	e(SYMBOL_OUTSIDE_SERVER_CONTEXT);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		iter = start;
		throw (e);
	}
	iter++;
	//	check that the server is opened with a '{'
	if (iter == end || dynamic_cast<KeyLeftCurlyBracket*>(*iter) == NULL)
	{
		parse_exception	e(NO_SERVER_BODY);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		iter = start;
		throw (e);
	}
	iter++;
	//	try to create all the childred nodes of this tree.
	//	check that the server is closed by with a '}'
	if (iter == end || dynamic_cast<KeyRightCurlyBracket*>(*iter) == NULL)
	{
		parse_exception	e(UNCLOSED_SERVER_BODY);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		iter = start;
		throw (e);
	}
	iter++;
	
	ServerSymbol			*symbol = new ServerSymbol();
	Tree<ANonTerminal*>		*tree = Tree<ANonTerminal*>::makeTreeNode(symbol);
	return (tree);
}


