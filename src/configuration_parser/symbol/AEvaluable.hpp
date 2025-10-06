#pragma once

#include <ASymbol.hpp>
#include <Tree.hpp>

class AEvaluable : public ASymbol
{
	private:
	protected:
	public:
		AEvaluable(void);
		virtual	~AEvaluable(void);
		
		virtual AEvaluable*	clone(void) const = 0;

//		virtual void	evaluate(Tree<AEvaluable*> *self) = 0;
};
