#include <ParsingRuleAnd.hpp>
#include <parse_exception.hpp>
#include <Tree.hpp>
#include <ANonTerminal.hpp>
#include <AParser.hpp>

void	print_ast(Tree<AEvaluable*> *ast, size_t depth = 0);

ParsingRuleAnd::ParsingRuleAnd(AParsingRule *first_rule, ...)
{
	va_list args;
	va_start(args, first_rule);

	this->_rules.push_back(first_rule);
	AParsingRule	*rule = va_arg(args, AParsingRule *);
	while (rule)
	{
		this->_rules.push_back(rule);
		rule = va_arg(args, AParsingRule *);
	}
}

ParsingRuleAnd::~ParsingRuleAnd(void)
{
	size_t	i = 0;
	while (i < this->_rules.size())
	{
		delete (this->_rules[i]);
		i++;
	}
}

std::vector<Tree<AEvaluable*>*>	ParsingRuleAnd::consumeTerminals(terminal_iter &iter, const terminal_iter &end) const
{
	std::vector<Tree<AEvaluable*>*>	return_val;
	std::vector<Tree<AEvaluable*>*>	temp_vector;
	size_t	i = 0;
	try
	{
		while (i < this->_rules.size())
		{
			temp_vector = this->_rules[i]->consumeTerminals(iter, end);
			return_val.insert(return_val.end(), temp_vector.begin(), temp_vector.end());
			i++;
		}
	}
	catch (...)
	{
		i = 0;
		while (i < return_val.size())
		{
			delete (return_val[i]);
			i++;
		}
		i = 0;
		while (i < temp_vector.size())
		{
			delete (temp_vector[i]);
			i++;
		}
		throw ;
	}
	return (return_val);
}

//		parse_exception e(UNRECOGNIZED_SYMBOL);
//		e.setLine((*iter)->getLine());
//		e.setColumn((*iter)->getColumn());
//		e.setSize((*iter)->getSize());
//
