#pragma once


#include <string>
#include <iostream>

#include <ASymbol.hpp>


class ATerminal : public ASymbol
{
	private:
	protected:
		std::string _text;
	public:
		ATerminal(void);
//		ATerminal(const ATerminal & src);
//		ATerminal & operator = (const ATerminal & src);
		//	no need to have a destructor.
		//it will be inherited by the base class (ASymbol) and set by the subclases.

		//	this will find the size that the terminal should have on the string.
		virtual size_t		getTerminalSizeOnStr(const std::string & str) const = 0;

		//	this only worw over the _text variable.
		void		setText(const std::string & text);
		std::string	getText(void) const;
		size_t		getTextLength(void) const;
		
		virtual ATerminal*	clone(void) const = 0;
};
