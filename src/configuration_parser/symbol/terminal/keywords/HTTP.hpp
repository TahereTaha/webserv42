#pragma once

#include <iostream>
#include <AKeyword.hpp>


class HTTP : public AKeyword
{
	private:
	protected:
	public:
		HTTP(void);
		~HTTP(void);

		ATerminal*	clone(void) const;
};

