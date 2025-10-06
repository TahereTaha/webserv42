#pragma once

#include <vector>
#include <Tree.hpp>
#include <ANonTerminal.hpp>

#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>


class AParser
{
	private:
		//	codify the information about and, or, repetition, symple symbol.
		ANonTerminal	*_goal;
		AParsingRule	*_rule;

	protected:
	public:
		AParser(ANonTerminal *goal, AParsingRule *rule);
		~AParser(void);

		Tree<AEvaluable*>	*generateSubTree(terminal_iter &iter, const terminal_iter &end);
};

