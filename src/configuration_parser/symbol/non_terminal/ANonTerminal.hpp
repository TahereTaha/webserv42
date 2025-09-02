#pragma once

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <Tree.hpp>
#include <parse_exception.hpp>

//	be able to create them with a iterator of the terminalList.

typedef std::vector<ATerminal*>::iterator terminal_iterator;

class ANonTerminal : public ASymbol
{
	private:
	protected:
	public:
		ANonTerminal(void);
		virtual	~ANonTerminal(void) = 0;
		//		virtual void	analyse(void) = 0;
};

