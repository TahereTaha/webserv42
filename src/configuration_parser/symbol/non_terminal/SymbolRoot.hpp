#pragma once

#include <vector>
#include <string>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolRoot : public ANonTerminal
{
	private:
		std::string	_path;
	protected:
	public:
		SymbolRoot(void);
		~SymbolRoot(void);

		const char		*what(void) const;
		SymbolRoot	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;

		std::string	getPath(void) const ;
};
