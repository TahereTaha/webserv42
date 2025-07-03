#pragma once

#include "../Terminal.hpp"
#include <vector>

typedef std::vector<Terminal*>::iterator TerminalIterator;

class TerminalVector
{
	private:
		Terminal 			*match;
		void 				setAll(std::string content);
	public:
		TerminalVector();
		~TerminalVector();
		std::vector<Terminal*> contents;

		void 				print();
};
