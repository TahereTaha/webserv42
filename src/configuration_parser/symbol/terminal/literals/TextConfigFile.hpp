#pragma once

#include <ATerminal.hpp>
#include <AEvaluable.hpp>
#include <stddef.h>

class TextConfigFile : public ATerminal, public AEvaluable
{
	private:
	protected:
	public:
		TextConfigFile(void);
		~TextConfigFile(void);

		const char	*what(void) const ;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		TextConfigFile*	clone(void) const;

		void	evaluate(Tree<AEvaluable*> *self);
};

