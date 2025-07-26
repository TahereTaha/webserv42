#pragma once

#include <ATerminal.hpp>

class WhiteSpace : public ATerminal
{
	private:
	protected:
	public:
		WhiteSpace(void);
		~WhiteSpace(void);
		
		const char	*what(void) const ;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;
};
