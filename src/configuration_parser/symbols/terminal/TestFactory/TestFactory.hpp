#pragma once 

#include "../Terminal.hpp"

class TestFactory : public Terminal
{
	public:
		TestFactory();
		TestFactory(const std::string &src);
		Terminal* clone(const std::string &str) const;
};