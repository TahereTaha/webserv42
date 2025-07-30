#include <Parser.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <WhiteSpace.hpp>
#include <ConfigFileLexer.hpp>
#include <parse_exception.hpp>
#include <multy_parse_exception.hpp>

#include <stddef.h>

Parser::Parser(const Args & args)
{
	this->_configFileName = args.getConfigFileName();
	std::cout << "parsing:" << std::endl;
}

Parser::~Parser(void)
{
	//	the destruction of the diferent elements.
}

void	Parser::readFile(void)
{
	std::cout << "->reading the config file." << std::endl;

	std::ifstream	file(this->_configFileName.c_str());
	if (!file.is_open())
		throw std::invalid_argument("unexistent or unaxesible file.");
	
	std::string	line;
	while (std::getline(file, line))
	{
		line += "\n";
		this->_configFileContent.push_back(line);
	}
}

void	Parser::addTerminalsToList(std::vector<ATerminal*> line)
{
	std::vector<ATerminal*>::iterator	lineIt = line.begin();
	
	while (lineIt != line.end())
	{
		if (!dynamic_cast<WhiteSpace*>(*lineIt))
			this->_terminalList.push_back((*lineIt)->clone());
		lineIt++;
	}
	lineIt = line.begin();
	while (lineIt != line.end())
	{
		delete (*lineIt);
		lineIt++;
	}
}

void	Parser::scanning(void)
{
	std::cout << "->scanning" << std::endl;

	ConfigFileLexer	lexer;

	size_t	i = 0;
	size_t	vector_size = this->_configFileContent.size();
	try
	{
		while (i < vector_size)
		{
			this->addTerminalsToList(lexer.tokenizeStr(this->_configFileContent[i]));
			i++;
		}
	}
	catch (parse_exception & e)
	{
		e.tryPromote(this->_configFileContent[e.getLine()]);

		multy_parse_exception	multy_e(e);

		multy_e.makeErrorMsg(this->_configFileName, this->_configFileContent);
		throw (multy_e);
	}
	//	this->printTerminalList();
}

void	Parser::parsing(void)
{
	std::cout << "\t-> parsing" << std::endl;
}

void	Parser::analysis(void)
{
	std::cout << "\t-> analysis" << std::endl;
}

void	Parser::transpiling(void)
{
	std::cout << "\t-> transpiling" << std::endl;
}

void	Parser::printTerminalList(void) const 
{
	std::cout << "this is the termital list:" << std::endl;

	size_t	i = 0;
	while (i < this->_terminalList.size())
	{
		std::cout << "  " << this->_terminalList[i]->what() << "  ";
		i++;
		if (i < this->_terminalList.size())
			std::cout << "|";
	}
	std::cout << std::endl;
}
