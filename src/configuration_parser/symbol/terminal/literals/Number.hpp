#pragma once

#include <stddef.h>

#include <ATerminal.hpp>
#include <AEvaluable.hpp>

class Number : public ATerminal, public AEvaluable
{
	private:
	protected:
	public:
		Number(void);
		~Number(void);

		const char	*what(void) const ;
		size_t		getTerminalSizeOnStr(const std::string & str) const;
		Number*	clone(void) const;

		void	evaluate(Tree<AEvaluable*> *self);
};
