#include <ParsingRuleOr.hpp>
#include <parse_exception.hpp>
#include <Tree.hpp>
#include <ANonTerminal.hpp>
#include <AParser.hpp>

ParsingRuleOr::ParsingRuleOr(AParsingRule *first_rule, ...)
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

ParsingRuleOr::~ParsingRuleOr(void)
{
	size_t	i = 0;
	while (i < this->_rules.size())
	{
		delete (this->_rules[i]);
		i++;
	}
}

std::vector<Tree<AEvaluable*>*>	ParsingRuleOr::consumeTerminals(terminal_iter &iter, const terminal_iter &end) const
{
	std::vector<terminal_iter>	branch_check_points;
	std::vector<Tree<AEvaluable*>*>	return_val;
	terminal_iter	start = iter;
	size_t	i = 0;
	while (i < this->_rules.size())
	{
		try
		{
			iter = start;
			return_val = this->_rules[i]->consumeTerminals(iter, end);
			break ;
		}
		catch (parse_exception & e)
		{
			(void)e;
			branch_check_points.push_back(iter);
			i++;
		}
	}
	if (return_val.size() == 0)
	{
		terminal_iter	last_check_point = branch_check_points[0];
		i = 1;
		while (i < branch_check_points.size())
		{
			if (last_check_point < branch_check_points[i])
				last_check_point = branch_check_points[i];
			i++;
		}
		parse_exception e(UNRECOGNIZED_SYMBOL);
		e.setLine((*last_check_point)->getLine());
		e.setColumn((*last_check_point)->getColumn());
		e.setSize((*last_check_point)->getSize());

		throw (e);
	}
	return (return_val);
}

//		parse_exception e(UNRECOGNIZED_SYMBOL);
//		e.setLine((*iter)->getLine());
//		e.setColumn((*iter)->getColumn());
//		e.setSize((*iter)->getSize());
//
//		throw (e);
