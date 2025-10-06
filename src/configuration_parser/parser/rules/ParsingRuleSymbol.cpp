#include <ParsingRuleSymbol.hpp>
#include <parse_exception.hpp>
#include <Tree.hpp>
#include <ANonTerminal.hpp>
#include <AParser.hpp>

ParsingRuleSymbol::ParsingRuleSymbol(const ASymbol *symbol)
{
	this->_symbol = symbol->clone();
}

ParsingRuleSymbol::~ParsingRuleSymbol(void)
{
	delete (this->_symbol);
}

std::vector<Tree<AEvaluable*>*>	ParsingRuleSymbol::consumeTerminals(terminal_iter &iter, const terminal_iter &end) const
{
	std::vector<Tree<AEvaluable*>*>	return_val;
	//	check if we need to generate any subtrees for this symbol.
	ANonTerminal	*nonTerminal = dynamic_cast<ANonTerminal*>(this->_symbol);
	if (nonTerminal)
	{
		AParser	*parser = nonTerminal->getParser();
		return_val.push_back(parser->generateSubTree(iter, end));
		return (return_val);
	}
	//	check if this simbol is in the current iterator of the terminal list.
	if (((void **)this->_symbol)[0] != ((void **)(*iter))[0])
	{
		parse_exception e(UNRECOGNIZED_SYMBOL);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		throw (e);
	}
	//	check if we need to store it in the ast or not.
	AEvaluable	*evaluable = dynamic_cast<AEvaluable*>(this->_symbol);
	if (evaluable)
	{
		return_val.push_back(Tree<AEvaluable*>::makeTreeNode(((AEvaluable*)*iter)->clone()));
	}
	iter++;
	return (return_val);
}

