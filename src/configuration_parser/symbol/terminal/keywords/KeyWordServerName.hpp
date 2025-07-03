#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordServerName : public ATerminal
{
	private:
	protected:
	public:
		KeyWordServerName(void);
		KeyWordServerName(std::string str);
		KeyWordServerName(const KeyWordServerName& other);
		KeyWordServerName& operator=(const KeyWordServerName& other);
		virtual Symbol* clone() const;
};

