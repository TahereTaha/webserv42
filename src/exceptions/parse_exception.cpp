#include <textColors.h>

#include <parse_exception.hpp>
#include <iostream>
#include <cassert>
#include <parse_errno_msg.h>
#include <sstream>

parse_exception::parse_exception(t_parse_errno type)
{
	assert((type > NO_ERROR && type < UNDEFINED_ERROR) \
			&& "the error type dosen't match any of the existent ones.");
	this->_errorType = type;
}

parse_exception::~parse_exception(void)
{
}

const char		*parse_exception::strerror(void) const 
{
	return (g_parse_errno_msg_type[this->_errorType]);
}

void	parse_exception::tryPromote(std::string line)
{
	assert((this->_errorType == UNRECOGNIZE_CHARACTER) \
			&& "this promoter can't promote anything that is not unrecognize_character." );
	if (line[this->getColumn()] != '"')
		return ;
	this->_errorType = UNCLOSED_QUOTE;
	this->setSize(line.size() - this->getColumn());
}

static std::string	getHighlight(std::string line, size_t column, size_t size)
{
	std::ostringstream	highlight;
	size_t				i = 0;

	highlight << GREEN;
	while (i < line.size() && i < column)
	{
		if (line[i] == '\t')
			highlight << "    ";
		else if (line[i] != '\n')
			highlight << " ";
		i++;
	}
	if (i < line.size())
	{
		highlight << "^";
		i++;
	}
	while (i < line.size() && size)
	{
		if (line[i] == '\t')
			highlight << "~~~~";
		else if (line[i] != '\n')
			highlight << "~";
		i++;
		size--;
	}
	highlight << "\n";
	highlight << RESET;
	return (highlight.str());
}

static std::string	sed(std::string str, std::string find, std::string replacement)
{
	size_t	i = 0;
	
	while (i < str.size())
	{
		i = str.find(find, i);
		if (i == ((size_t) -1 ))
			break ;
		str.replace(i, find.size(), replacement);
		i += replacement.size();
	}
	return (str);
}

static std::string	getPosVisualAid(const std::vector<std::string> & fileContent, \
									size_t line, size_t column, size_t size)
{
	size_t	vector_size = fileContent.size();
	size_t	i = 0;

	while (i < line && i < vector_size)
		i++;

	std::ostringstream	posVisualAid;
	while (i < vector_size)
	{
		posVisualAid << sed(fileContent[i], "\t", "    ");
		posVisualAid << getHighlight(fileContent[i], column, size);
		if (size <= (fileContent[i].size() - column))
			break;
		size -= fileContent[i].size() - column;
		column = 0;
		i++;
	}
	return (posVisualAid.str());
}

void	parse_exception::makeErrorMsg(	const std::string & fileName, \
										const std::vector<std::string> & fileContent)
{
	(void) fileName;
	(void) fileContent;
	std::ostringstream	errorMsg;

	//	adding the error type.
	errorMsg << "\n" << CYAN << this->strerror() << RESET << "\n";
	//	adding the positon
	errorMsg << fileName << ":" << this->getLine() + 1 <<  ":" << this->getColumn() + 1 << "\n";
	//	some visual aid to the position.
	errorMsg << getPosVisualAid(fileContent, this->getLine(), this->getColumn(), this->getSize());
	this->_errorMsg = errorMsg.str();
}

std::string	parse_exception::what(void) const 
{
	return (this->_errorMsg);
}

void	parse_exception::setLine(size_t line)
{
	this->_line = line;
}

void	parse_exception::setColumn(size_t column)
{
	this->_column = column;
}

void	parse_exception::setSize(size_t size)
{
	this->_size = size;
}

size_t	parse_exception::getLine(void) const
{
	return (this->_line);
}

size_t	parse_exception::getColumn(void) const
{
	return (this->_column);
}

size_t	parse_exception::getSize(void) const
{
	return (this->_size);
}

