#pragma once

#include <vector>
#include <cstdarg>
#include <AParsingRule.hpp>
#include <ASymbol.hpp>

class ParsingRuleAnd : public AParsingRule
{
	private:
		std::vector<AParsingRule *>	_rules;
	protected:
	public:
		ParsingRuleAnd(AParsingRule *rule, ...); // needs to be null terminated.
		~ParsingRuleAnd(void);
		
		std::vector<Tree<AEvaluable*>*>	consumeTerminals(terminal_iter &iter, const terminal_iter &end) const;
};
