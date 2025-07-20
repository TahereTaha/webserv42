#pragma once

#include <Aparse_exception.hpp>
#include <string>
#include <stddef.h>
#include <vector>

class parse_exception : public Aparse_exception
{
	private:
//		size_t		_line;
//		size_t		_colum;
//		size_t		_size;
//		std::string	_errorMsgPlace;
//		std::string	_errorMsgTip;

		void		makeErrorMsgType(void);
	protected:
	public:
		parse_exception(t_parse_errno type);
		~parse_exception(void);

		void	makeErrorMsg(void);

//		void		makeErrorMsgPlace(vector<std::string> lines);
};


