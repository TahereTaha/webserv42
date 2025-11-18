#include <ConfigurationParser.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <WhiteSpace.hpp>
#include <ConfigFileLexer.hpp>
#include <parse_exception.hpp>
#include <multy_parse_exception.hpp>
#include <SymbolConfigContext.hpp>
#include <AParser.hpp>

#include <stddef.h>

ConfigurationParser::ConfigurationParser(const Args & args)
{
	this->_AST = NULL;
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
	delete (this->_AST);
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
			this->_terminalList.push_back(dynamic_cast<ATerminal*>((*lineIt)->clone()));
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

	std::vector<ATerminal *>::iterator	iter = this->_terminalList.begin();
	std::vector<ATerminal *>::iterator	end = this->_terminalList.end();

	AParser	*parser = SymbolConfigContext().getParser();

	try 
	{
		this->_AST = parser->generateSubTree(iter, end);
	}
	// wrap correctly any parsing errors.
	catch (parse_exception & e)
	{
		multy_parse_exception	multy_e(e);

		multy_e.makeErrorMsg(this->_configFileName, this->_configFileContent);
		throw (multy_e);
	}
	// checking if there are still tokens left to consume.
	if (iter != end)
	{
		parse_exception	e(UNRECOGNIZED_SYMBOL);
		e.setLine((*iter)->getLine());
		e.setColumn((*iter)->getColumn());
		e.setSize((*iter)->getSize());

		multy_parse_exception	multy_e(e);

		multy_e.makeErrorMsg(this->_configFileName, this->_configFileContent);
		throw (multy_e);
	}
	this->printAST();
}

void	ConfigurationParser::analysis(void)
{
	std::cout << "\t-> analysis" << std::endl;

	Tree<AEvaluable*>::iterator	iter = this->_AST->begin();
	Tree<AEvaluable*>::iterator	end = this->_AST->end();

	while (iter != end)
	{
		(*iter)->getContent()->evaluate(*iter);
		iter++;
	}
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
	}
	std::cout << std::endl;
}

static void align_tabulation(size_t	depth)
{
	size_t	i = 0;
	while (i < depth)
	{
		std::cout << "   >";
		i++;
	}
}

static void	print_ast(Tree<AEvaluable*> *ast, size_t depth = 0)
{
	if (ast->getNodeType() == LEAF)
	{
		align_tabulation(depth);
		std::cout << ast->getContent()->what();
		std::cout << " with a id of: " << (void *) ast->getContent() << ";\n";
		return ;
	}

	align_tabulation(depth);
	std::cout << ast->getContent()->what();
	std::cout << " with a id of: " << (void *) ast->getContent() << "\n";

	align_tabulation(depth);
	std::cout << "{\n";
	
	Tree<AEvaluable*>	*node = (*ast)[0];
	while (node)
	{
		print_ast(node, depth + 1);
		node = node->getRightBranchNode();
	}
	
	align_tabulation(depth);
	std::cout << "}\n";
}

void	ConfigurationParser::printAST(void) const
{
	print_ast(this->_AST);
}

