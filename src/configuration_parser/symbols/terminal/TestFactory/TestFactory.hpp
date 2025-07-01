#pragma once 

#include "../Terminal.hpp"

class TestFactory : public Terminal
{
	public:
		TestFactory();
		TestFactory(std::string src);
		~TestFactory();

		Terminal* clone() const;
		void setText(const std::string &text);
};