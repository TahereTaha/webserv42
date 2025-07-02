#pragma once

#include "Terminal.hpp"

class Semicolon : public Terminal
{
	private:
	protected:
	public:
		Semicolon(void);
		Semicolon(std::string str);
		Semicolon(const Semicolon& other);
		Semicolon& operator=(const Semicolon& other);
};

