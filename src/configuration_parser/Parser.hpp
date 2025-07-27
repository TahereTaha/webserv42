#pragma once 

#include <string>
#include <vector>

#include <ASymbol.hpp>
#include <ATerminal.hpp>
#include <Args.hpp>

//	this class in responsible for reading the file and seting up all the needed
//	object for the web server to run.
class Parser
{
	private:
		std::string			_configFileName;
		std::vector<std::string>	_configFileContent;
		std::vector<ATerminal*>	_terminalList;		//	this for the future make it nested in a tree 
//		tree<ASymbol*>		_AST;

		void	addTerminalsToList(std::vector<ATerminal*> line);

		void	printTerminalList(void) const ;
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
