#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolServerName.hpp>

#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>


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


Tree<ANonTerminal*>		*SymbolServerName::generateSubTree(terminal_iterator &iter, \
				const terminal_iterator &end)
{
	std::vector<ATerminal*>::iterator start = iter;

	SymbolServerName			*symbol = new SymbolServerName();
	Tree<ANonTerminal*>		*tree = Tree<ANonTerminal*>::makeTreeNode(symbol);
	
	//	I alredy know that if this function is called 
	//	the first element will be the the server name key word
	iter++;
	if (iter == end || dynamic_cast<TextConfigFile*>(*iter) == NULL)
	{
		parse_exception	e(SERVER_NAME_DIRECTIVE_EXPECTS_TEXT);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		iter = start;
		throw (e);
	}
	symbol->setName((*iter)->getText());
	iter++;
	if (iter == end || dynamic_cast<KeySemicolon*>(*iter) == NULL)
	{
		iter = start;
		parse_exception	e(UNCLOSED_SERVER_NAME_DIRECTIVE);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		throw (e);
	}
	iter++;
	return (tree);
}

void	SymbolServerName::setName(std::string name)
{
	this->_name = name;
}

std::string	SymbolServerName::getName(void) const 
{
	return (this->_name);
}
