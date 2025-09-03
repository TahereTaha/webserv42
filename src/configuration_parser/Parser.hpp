#pragma once 

#include <string>
#include <vector>

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <Args.hpp>
#include <Tree.hpp>

//	this class in responsible for transforming the file in the IR for the web server to execute.
class Parser
{
	private:
		std::string							_configFileName;
		std::vector<std::string>			_configFileContent;
		std::vector<ATerminal*>				_terminalList;
		std::vector<Tree<ANonTerminal*>*>	_ASTList;


		void	addTerminalsToList(std::vector<ATerminal*> line);
		void	printTerminalList(void) const ;
		void	printASTList(void) const ;
		void	printAST(Tree<ANonTerminal*>*ast) const ;

	protected:
	public:
		Parser(const Args & args);
		~Parser(void);
		void	readFile(void);
		void	scanning(void);
		void	parsing(void);
		void	analysis(void);
		void	transpiling(void);
};
