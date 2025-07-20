#pragma once

#include <iostream>
#include <AKeyWord.hpp>


class HTTP : public AKeyWord
{
	private:
	protected:
	public:
		HTTP(void);
		~HTTP(void);

		ATerminal*	clone(void) const;
};

