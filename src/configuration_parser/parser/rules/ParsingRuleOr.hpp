#pragma once

#include <vector>
#include <cstdarg>
#include <AParsingRule.hpp>
#include <ASymbol.hpp>

class ParsingRuleOr : public AParsingRule
{
	private:
		std::vector<AParsingRule *>	_rules;
	protected:
	public:
		ParsingRuleOr(AParsingRule *rule, ...); // needs to be null terminated.
		~ParsingRuleOr(void);

		std::vector<Tree<AEvaluable*>*>	consumeTerminals(terminal_iter &iter, const terminal_iter &end) const;
};
