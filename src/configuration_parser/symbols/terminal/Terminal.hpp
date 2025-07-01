#pragma once

#include <string>
#include "Symbol.hpp"
#include <cstring>

class Terminal : public Symbol
{
	private:
	protected:
		std::string _text;
		int get_match(const std::string &src, const std::string &pattern);
		std::string get_pattern(const std::string &src, const std::string &pattern);
	public:
		Terminal();
		virtual Terminal* clone (const std::string& str) const = 0;
		std::string getText() const { return _text; }
};


Terminal::Terminal() : _text("") {}

int Terminal::get_match(const std::string &src, const std::string &pattern)
{
	int i = 0;
	while (strchr(pattern.c_str(), src[i]) != nullptr && src[i] != '\0')
		i++;
	return (i);
}

std::string Terminal::get_pattern(const std::string &src, const std::string &pattern)
{
	int i = get_match(src, pattern);
	return (src.substr(0, i));
}