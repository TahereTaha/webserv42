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
		
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;

		int			getValue(void) const;
};
