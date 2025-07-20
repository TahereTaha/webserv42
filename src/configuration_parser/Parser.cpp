#include <Parser.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <WhiteSpace.hpp>
#include <ConfigFileLexer.hpp>

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
		this->_configFileContent.push_back(line);
	}
}

void	Parser::addTerminalsToList(std::vector<ASymbol*> line)
{
	std::vector<ASymbol*>::iterator	lineIt = line.begin();
	
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
	while (i < vector_size)
	{
		this->addTerminalsToList(lexer.tokenizeStr(this->_configFileContent[i]));
		i++;
	}
}

void	Parser::syntaxAnalysis(void)
{
	std::cout << "->syntax analysis" << std::endl;
}

void	Parser::semanticAnalysis(void)
{
	std::cout << "->semantic analysis" << std::endl;
}

void	Parser::initializeServer(void)
{
	std::cout << "->initializing the server." << std::endl;
}

