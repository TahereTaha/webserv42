#pragma once

#include "../Terminal.hpp"
#include <vector>

typedef std::vector<Terminal*>::iterator TerminalIterator;

class TerminalVector
{
	public:
		TerminalVector();
		~TerminalVector();
		std::vector<Terminal*> contents;

		Terminal 			*match;
		void 				setAll(std::string content);
		void 				print();
};