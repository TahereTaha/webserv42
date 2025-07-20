#include <parse_exception.hpp>
#include <iostream>

parse_exception::parse_exception(t_parse_errno type) :Aparse_exception(type)
{
	std::cout << "DEBUG:: it is making the correct thing.";
}

parse_exception::~parse_exception(void)
{
}

void	parse_exception::makeErrorMsg(void)
{
	std::cout << "DEBUG:: it is entering in here." << std::endl;
	this->_errorMsg = "";
	this->makeErrorMsgType();
}

void	parse_exception::makeErrorMsgType(void)
{
	this->_errorMsg += this->strerror();
	std::cout << "DEBUG:: in make error msg the msg is:" << this->_errorMsg << std::endl;
}

