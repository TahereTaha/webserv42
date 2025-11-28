#pragma once 

#include <string>
#include <vector>

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <AEvaluable.hpp>
#include <Args.hpp>
#include <Tree.hpp>

#include <intermediate_representation.hpp>

//	this class in responsible for transforming the file in the IR for the web server to execute.
class ConfigurationParser
{
	private:
		std::string							_configFileName;
		std::vector<std::string>			_configFileContent;
		std::vector<ATerminal*>				_terminalList;
		Tree<AEvaluable*>					*_AST;

		void	addTerminalsToList(std::vector<ATerminal*> line);
		void	printTerminalList(void) const ;
		void	printAST(void) const ;

	protected:
	public:
		ConfigurationParser(const Args & args);
		~ConfigurationParser(void);
		void	readFile(void);
		void	scanning(void);
		void	parsing(void);
		void	analysis(void);
		std::vector<t_server>	getServers(void) const ;
};
