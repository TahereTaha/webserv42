#pragma once

#include <ATerminal.hpp>

class KeyPoint : public ATerminal
{
	private:
	protected:
	public:
		KeyPoint(void);
		~KeyPoint(void);
		
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;
};

