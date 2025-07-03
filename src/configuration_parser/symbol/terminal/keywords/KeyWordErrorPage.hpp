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
		void setText(const std::string& str);
};

