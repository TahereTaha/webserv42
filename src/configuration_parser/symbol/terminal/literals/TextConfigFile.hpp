#pragma once

#include <ATerminal.hpp>
#include <stddef.h>

class TextConfigFile : public ATerminal
{
	private:
	protected:
	public:
		TextConfigFile(void);
		~TextConfigFile(void);

		size_t		getTerminalSizeOnStr(const std::string & str) const;
		ATerminal*	clone(void) const;

		std::string	getValue(void) const;
};

