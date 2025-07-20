#include <string>
#include <Aparse_exception.hpp>
#include <parse_errno_msg.h>

Aparse_exception::Aparse_exception(t_parse_errno type)
{
	this->_errorType = type;
}

Aparse_exception::~Aparse_exception(void)
{
}

//void	Aparse_exception::makeErrorMsg(void)
//{
//}

std::string	Aparse_exception::what(void) const 
{
	return (this->_errorMsg);
}

t_parse_errno	Aparse_exception::getErrorType(void) const
{
	return (this->_errorType);
}

void		Aparse_exception::setErrorType(t_parse_errno newType)
{
	this->_errorType = newType;
}

const char		*Aparse_exception::strerror(void) const 
{
	return (g_parse_errno_msg_type[this->_errorType]);
}

