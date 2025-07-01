#pragma once

#include <string>
#include "../Symbol.hpp"
#include <cstring>
#include <iostream>
class Terminal : public Symbol
{
	private:
	protected:
		std::string _text;
	public:
		Terminal();
		virtual ~Terminal() = default;
		virtual Terminal* clone (const std::string& str) const = 0;
		std::string getText() const { return _text; }
};


int get_match(const std::string &src, const std::string &pattern);
std::string get_pattern(const std::string &src, const std::string &pattern);
