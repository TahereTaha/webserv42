#pragma once

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <AEvaluable.hpp>
#include <Tree.hpp>
#include <parse_exception.hpp>

//	be able to create them with a iterator of the terminalList.


class ANonTerminal : public AEvaluable
{
	private:
	protected:
	public:
		ANonTerminal(void);
		virtual	~ANonTerminal(void) = 0;

		virtual	AParser	*getParser(void) const = 0;
};
