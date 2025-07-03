#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordErrorPage : public ATerminal
{
	private:
	protected:
	public:
		KeyWordErrorPage(void);
		KeyWordErrorPage(std::string str);
		KeyWordErrorPage(const KeyWordErrorPage& other);
		KeyWordErrorPage& operator=(const KeyWordErrorPage& other);
		virtual Symbol* clone() const;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
};

