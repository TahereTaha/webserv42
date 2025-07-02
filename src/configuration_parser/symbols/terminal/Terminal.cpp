
#include "Terminal.hpp"

Terminal::Terminal() : _text("") {}

int get_match(const std::string &src, const std::string &pattern)
{
	int i = 0;
	while (strchr(pattern.c_str(), src[i]) != nullptr && src[i] != '\0')
		i++;
	return (i);
}

std::string get_pattern(const std::string &src, const std::string &pattern)
{
	int i = get_match(src, pattern);
	return (src.substr(0, i));
}

Terminal::~Terminal() {}
