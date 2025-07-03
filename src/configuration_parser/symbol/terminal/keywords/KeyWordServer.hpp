#pragma once

#include <iostream>
#include "ATerminal.hpp"

class KeyWordServer : public ATerminal
{
	private:
	protected:
	public:
		KeyWordServer(void);
		KeyWordServer(std::string str);
		KeyWordServer(const KeyWordServer& other);
		KeyWordServer& operator=(const KeyWordServer& other);
		virtual Symbol* clone() const;
};

