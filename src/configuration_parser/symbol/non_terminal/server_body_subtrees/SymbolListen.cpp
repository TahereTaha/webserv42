#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolListen.hpp>

#include <KeyWordListen.hpp>
#include <KeySemicolon.hpp>

SymbolListen::SymbolListen(void)
{
}

SymbolListen::~SymbolListen(void)
{
}

const char	*SymbolListen::what(void) const 
{
	return ("listen_symbol");
}

Tree<ANonTerminal*>		*SymbolListen::generateSubTree(terminal_iterator &iter, \
				const terminal_iterator &end)
{
	std::vector<ATerminal*>::iterator start = iter;

	SymbolServer			*symbol = new SymbolListen();
	Tree<ANonTerminal*>		*tree = Tree<ANonTerminal*>::makeTreeNode(symbol);
	
	Tree<ANonTerminal*>		*subTree;

	iter++;
	try
	{
		subTree = SymbolSocket::generateSubTree(iter, end);
	}
	catch (parse_exception & e)
	{
		iter = start;
		delete (tree);
		throw(e);
	}
	while (subTree)
	{
		try
		{
			tree->addTreeAsChild(subTree);
			subTree = SymbolSocket::generateSubTree(iter, end);
		}
		catch (parse_exception & e)
		{
			iter = start;
			delete (tree);
			throw(e);
		}
	}
	//	test if it is closed by a semicolon.
	if (iter == end || dynamic_cast<KeySemicolon*>(*iter) == NULL)
	{
		iter = start;
		parse_exception	e(UNCLOSED_SERVER_NAME_DIRECTIVE);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		delete (tree);
		throw (e);
	}
	iter++;
	return (tree);
}
