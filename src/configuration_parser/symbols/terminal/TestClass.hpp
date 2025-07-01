#pragma once 

#include <Terminal.hpp>

class TestPattern : public Terminal
{
	public:
		TestPattern();
		TestPattern(const std::string &src);
		Terminal* clone(const std::string &str) const;
};