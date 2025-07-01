#pragma once

#include "../Terminal.hpp"
#include <vector>

class TerminalVector : public std::vector<Terminal*>
{
	private:
	public:
		TerminalVector();
		~TerminalVector();

		Terminal 			*match;
		void 				setAll(std::string content);
};