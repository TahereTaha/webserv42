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
};

