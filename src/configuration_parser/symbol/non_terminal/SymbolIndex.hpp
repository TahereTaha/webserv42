#pragma once

#include <vector>
#include <string>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

class SymbolIndex : public ANonTerminal
{
	private:
		std::vector<std::string>	_indexFiles;
	protected:
	public:
		SymbolIndex(void);
		~SymbolIndex(void);

		const char		*what(void) const;
		SymbolIndex	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;

		std::vector<std::string>	getIndexFiles(void) const ;
};
