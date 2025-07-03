#pragma once

#include <iostream>
#include <ATerminal.hpp>
#include <StrMatchUtils.hpp>

class ErrorPage : public ATerminal
{
	private:
	protected:
	public:
		ErrorPage(void);
		~ErrorPage(void);

		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;
};

