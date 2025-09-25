#include <ConfigurationParser.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <WhiteSpace.hpp>
#include <ConfigFileLexer.hpp>
#include <parse_exception.hpp>
#include <multy_parse_exception.hpp>
//#include <SymbolServer.hpp>

#include <stddef.h>

ConfigurationParser::ConfigurationParser(const Args & args)
{
	this->_configFileName = args.getConfigFileName();
	std::cout << "parsing:" << std::endl;
}

ConfigurationParser::~ConfigurationParser(void)
{
	size_t	i = 0;
	while (i < this->_terminalList.size())
	{
		delete (this->_terminalList[i]);
		i++;
	}
	i = 0;
	while (i < this->_ASTList.size())
	{
		delete (this->_ASTList[i]);
		i++;
	}
	//	the destruction of the diferent elements.
}

void	ConfigurationParser::readFile(void)
{
	std::cout << "\t->reading the config file." << std::endl;

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

void	ConfigurationParser::addTerminalsToList(std::vector<ATerminal*> line)
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

void	ConfigurationParser::scanning(void)
{
	std::cout << "\t->scanning" << std::endl;

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
	this->printTerminalList();
}

void	ConfigurationParser::parsing(void)
{
	std::cout << "\t-> parsing " << std::endl;
	
//	std::vector<ATerminal *>::iterator	iter = this->_terminalList.begin();
//	std::vector<ATerminal *>::iterator	end = this->_terminalList.end();
//
//	while (iter != end)	//	heach time a new server is created the iter is moved forward.
//	{
//		try
//		{
//			this->_ASTList.push_back(SymbolServer::generateSubTree(iter, end));
//		}
//		catch (parse_exception & e)
//		{
//			multy_parse_exception	multy_e(e);
//
//			multy_e.makeErrorMsg(this->_configFileName, this->_configFileContent);
//			throw (multy_e);
//		}
//	}
//	this->printASTList();
}

void	ConfigurationParser::analysis(void)
{
	std::cout << "\t-> analysis" << std::endl;
}

void	ConfigurationParser::transpiling(void)
{
	std::cout << "\t-> transpiling" << std::endl;
}

void	ConfigurationParser::printTerminalList(void) const 
{
	std::cout << "this is the termital list:" << std::endl;

	size_t	i = 0;
	while (i < this->_terminalList.size())
	{
		std::cout << "  " << this->_terminalList[i]->what() << "\n";
		i++;
//		if (i < this->_terminalList.size())
//			std::cout << "|";
	}
	std::cout << std::endl;
}

void	ConfigurationParser::printASTList(void) const 
{
	size_t	i = 0;
	while (i < this->_ASTList.size())
	{
		std::cout << "server n" << i << ":" << std::endl;
		this->printAST(this->_ASTList[i]);
		std::cout << std::endl;
		i++;
	}
}

void	ConfigurationParser::printAST(Tree<ANonTerminal*> *ast) const
{
	if (ast->getNodeType() == LEAF)
	{
		std::cout << ast->getContent()->what() << "; ";
		return ;
	}
	std::cout << ast->getContent()->what() << " { ";
	Tree<ANonTerminal*>	*node = (*ast)[0];
	while (node)
	{
		this->printAST(node);
		node = node->getRightBranchNode();
	}
	std::cout << " } ";
}

