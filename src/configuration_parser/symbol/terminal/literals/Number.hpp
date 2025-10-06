#pragma once

#include <stddef.h>

#include <ATerminal.hpp>

class Number : public ATerminal
{
	private:
	protected:
	public:
		Number(void);
		~Number(void);
		
		const char	*what(void) const ;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ASymbol*	clone(void) const;

		int			getValue(void) const;
};
