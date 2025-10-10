#include <ParsingRuleRepetition.hpp>
#include <parse_exception.hpp>
#include <Tree.hpp>
#include <ANonTerminal.hpp>
#include <AParser.hpp>

ParsingRuleRepetition::ParsingRuleRepetition(size_t	min, size_t	max, AParsingRule *rule)
{
	this->_min = min;
	this->_max = max;
	this->_rule = rule;
}

ParsingRuleRepetition::~ParsingRuleRepetition(void)
{
	delete (this->_rule);
}

std::vector<Tree<AEvaluable*>*>	ParsingRuleRepetition::consumeTerminals(terminal_iter &iter, const terminal_iter &end) const
{
	std::vector<Tree<AEvaluable*>*>	return_val;
	std::vector<Tree<AEvaluable*>*>	tmp_vector;
	size_t	i = 0;
	while (i < this->_max)
	{
		try
		{
			tmp_vector = this->_rule->consumeTerminals(iter, end);
			i++;
		}
		catch (parse_exception & e)
		{
			if (i < this->_min || i > this->_max)
				throw (e);
			break ;
		}
		return_val.insert(return_val.end(), tmp_vector.begin(), tmp_vector.end());
	}
	return (return_val);
}

//		parse_exception e(UNRECOGNIZED_SYMBOL);
//		e.setLine((*iter)->getLine());
//		e.setColumn((*iter)->getColumn());
//		e.setSize((*iter)->getSize());
//
//		throw (e);
