#include <parse_exeption.hpp>

parse_exception::parse_exception(t_errorType type) :Aparse_exception(type)
{
}

parse_exception::~parse_exception(void)
{
}

void	parse_exception::makeErrorMsg(void)
{
	this->_errorMsg = "";
	this->makeErrorType(void);
}

void	parse_exception::makeErrorMsgType(void)
{
	this->_errorMsg += this->strerror(void);
}

