#pragma once

#include <AParsingRule.hpp>
#include <ASymbol.hpp>

class ParsingRuleSymbol : public AParsingRule
{
	private:
		ASymbol	*_symbol;
	protected:
	public:
		ParsingRuleSymbol(const ASymbol *symbol);
		~ParsingRuleSymbol(void);
		
		std::vector<Tree<AEvaluable*>*>	consumeTerminals(terminal_iter &iter, const terminal_iter &end) const;
};
