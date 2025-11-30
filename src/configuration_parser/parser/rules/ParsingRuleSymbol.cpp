#include <ParsingRuleSymbol.hpp>
#include <parse_exception.hpp>
#include <Tree.hpp>
#include <ANonTerminal.hpp>
#include <AParser.hpp>

#include <SymbolReturn.hpp>

ParsingRuleSymbol::ParsingRuleSymbol(const ASymbol *symbol)
{
	this->_symbol = symbol->clone();
	delete (symbol);
}

ParsingRuleSymbol::~ParsingRuleSymbol(void)
{
	delete (this->_symbol);
}

std::vector<Tree<AEvaluable*>*>	ParsingRuleSymbol::consumeTerminals(terminal_iter &iter, const terminal_iter &end) const
{
	std::vector<Tree<AEvaluable*>*>	return_val;
	if (iter == end)
	{
		iter--;
		parse_exception e(ALL_SYMBOLS_CONSUMED);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn() + (*iter)->getSize());
		e.setSize(1);

		throw (e);
	}
	//	check if we need to generate any subtrees for this symbol.
	ANonTerminal	*nonTerminal = dynamic_cast<ANonTerminal*>(this->_symbol);
	if (nonTerminal)
	{
		AParser	*parser = nonTerminal->getParser();
		return_val.push_back(parser->generateSubTree(iter, end));
		delete (parser);
		return (return_val);
	}
	//	check if this simbol is in the current iterator of the terminal list.
	ASymbol	*symbol = dynamic_cast<ASymbol*>(*iter);
	if (((void **)this->_symbol)[0] != ((void **)symbol)[0])
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
		return_val.push_back(Tree<AEvaluable*>::makeTreeNode((dynamic_cast<AEvaluable*>(*iter))->clone()));
	}
	iter++;
	return (return_val);
}

