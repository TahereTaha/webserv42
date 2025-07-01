#pragma once

#include "../Symbol.hpp"
#include "iostream"
#include "./TestFactory/TypeTerminalVector.hpp"

class TerminalFactory
{
	private:
		TerminalFactory(const TerminalFactory &src);

		int					pushBack(std::string content);
	protected:
		TerminalVector		_tokenVector;
		TerminalVector		_constructors;
	public:
		TerminalFactory(void);

		virtual 			~TerminalFactory();

		int 				Lexer(std::string content);
		TerminalVector		getContent() const { return _tokenVector; }
};

std::ostream& operator<<(std::ostream& os, const TerminalFactory& tf);


