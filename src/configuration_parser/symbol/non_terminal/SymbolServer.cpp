#include <subTreeGenerationUtils.hpp>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolServer.hpp>

#include <KeyWordServer.hpp>
#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>


SymbolServer::SymbolServer(void)
{
}

SymbolServer::~SymbolServer(void)
{
}

const char	*SymbolServer::what(void) const
{
	return ("server_symbol");
}

Tree<ANonTerminal*>		*SymbolServer::generateSubTree(terminal_iterator &iter, \
				const terminal_iterator &end)
{
	std::vector<ATerminal*>::iterator start = iter;

	SymbolServer			*symbol = new SymbolServer();
	Tree<ANonTerminal*>		*tree = Tree<ANonTerminal*>::makeTreeNode(symbol);
	
	Tree<ANonTerminal*>		*subTree;

	//	check that it starts with a server keyword.
	if (iter == end || dynamic_cast<KeyWordServer*>(*iter) == NULL)
	{
		parse_exception	e(UNRECOGNIZED_SYMBOL);
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
	try 
	{
		subTree = generateServerBodySubTree(iter, end);
	}
	catch (parse_exception & e)
	{
		iter = start;
		throw(e);
	}
	while (subTree)
	{
		try
		{
			tree->addTreeAsChild(subTree);
			subTree = generateServerBodySubTree(iter, end);
		}
		catch (parse_exception & e)
		{
			iter = start;
			throw(e);
		}
	}

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

	return (tree);
}


