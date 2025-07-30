#include <sstream>

#include <textColors.h>

#include <parse_exception.hpp>
#include <multy_parse_exception.hpp>

multy_parse_exception::multy_parse_exception(void)
{
}

multy_parse_exception::multy_parse_exception(parse_exception exception)
{
	this->_errorVector.push_back(exception);
}

multy_parse_exception::multy_parse_exception(std::vector<parse_exception> exceptionVector)
{
	this->_errorVector = exceptionVector;
}

void	multy_parse_exception::addException(parse_exception exception)
{
	this->_errorVector.push_back(exception);
}

void	multy_parse_exception::makeErrorMsg(const std::string & fileName, \
											const std::vector<std::string> & fileContent)
{
	std::ostringstream	errorMsg;

	errorMsg << "\nthere are: " << RED << this->_errorVector.size() << " errors" << RESET << ".\n";

	size_t	i = 0;
	while (i < this->_errorVector.size())
	{
		this->_errorVector[i].makeErrorMsg(fileName, fileContent);
		errorMsg << this->_errorVector[i].what();
		i++;
	}
	this->_errorMsg = errorMsg.str();
}

std::string		multy_parse_exception::what(void) const 
{
	return (this->_errorMsg);
}

