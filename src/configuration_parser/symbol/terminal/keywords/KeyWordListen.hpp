#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordListen : public ATerminal
{
	private:
	protected:
	public:
		KeyWordListen(void);
		KeyWordListen(std::string str);
		KeyWordListen(const KeyWordListen& other);
		KeyWordListen& operator=(const KeyWordListen& other);
		virtual Symbol* clone() const;
};

