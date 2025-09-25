#pragma once

#include <ASymbol.hpp>
#include <Tree.hpp>

class AEvaluable : public ASymbol
{
	private:
	protected:
	public:
		Aevaluable(void);
		virtual	~Aevaluable(void) = 0;

		virtual void	evaluate(Tree<AEvaluable*> *self) = 0;
};
