#pragma once

#include <string>
#include <vector>
#include <parse_exception.hpp>

class	multy_parse_exception
{
	private:
		std::string					_errorMsg;
		std::vector<parse_exeption>	_errorVector;
	protected:
	public:
		multy_parse_exeption();

		void		makeErrorMsg(void);
		std::string	what(void) const ;
};
