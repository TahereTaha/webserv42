#pragma once

#include <ASymbol.hpp>

class ParsingRuleSymbol : AParsingRule
{
	private:
		ASymbol	*_symbol;
	protected:
	public:
		ParsingRuleSymbol(const ASymbol *symbol);
		ParsingRuleSymbol(void);
};
