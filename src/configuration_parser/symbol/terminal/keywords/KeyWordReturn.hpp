#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordReturn : public ATerminal
{
	private:
	protected:
	public:
		KeyWordReturn(void);
		KeyWordReturn(std::string str);
		KeyWordReturn(const KeyWordReturn& other);
		KeyWordReturn& operator=(const KeyWordReturn& other);
		virtual Symbol* clone() const;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
};

