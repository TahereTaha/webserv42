#pragma once

#include <vector>
#include <AParsingRule.hpp>
#include <ASymbol.hpp>

class ParsingRuleRepetition : public AParsingRule
{
	private:
		size_t			_min;
		size_t			_max;
		AParsingRule	*_rule;
	protected:
	public:
		ParsingRuleRepetition(size_t min, size_t max, AParsingRule *rule);
		~ParsingRuleRepetition(void);

		std::vector<Tree<AEvaluable*>*>	consumeTerminals(terminal_iter &iter, const terminal_iter &end) const;
};
