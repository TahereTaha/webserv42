#pragma once

#include <Tree.hpp>
#include <vector>
#include <AEvaluable.hpp>
#include <ATerminal.hpp>

class AParsingRule
{
	private:
	protected:
	public:

		AParsingRule(void);
		virtual ~AParsingRule(void);

		virtual std::vector<Tree<AEvaluable*>*>	consumeTerminals(terminal_iter &iter, const terminal_iter &end) const = 0;
};
