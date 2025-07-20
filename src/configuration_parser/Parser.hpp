#include <string>
#include <vector>

#include <ASymbol.hpp>
#include <Args.hpp>

//	this class in responsible for reading the file and seting up all the needed
//	object for the web server to run.
class Parser
{
	private:
		std::string			_configFileName;
		std::vector<std::string>	_configFileContent;
		std::vector<ASymbol*>	_terminalList;		//	this for the future make it nested in a tree 
//		tree<ASymbol*>		_AST;

		void	addTerminalsToList(std::vector<ASymbol*> line);
	protected:
	public:
		Parser(const Args & args);
		~Parser(void);
		void	readFile(void);
		void	scanning(void);
		void	syntaxAnalysis(void);
		void	semanticAnalysis(void);
		void	initializeServer(void);
};
