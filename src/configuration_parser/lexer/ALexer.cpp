#include <ALexer.hpp>
#include <vector>
#include <Aparse_exception.hpp>

ALexer::ALexer(void)
{
}

ALexer::~ALexer(void)
{
	delete (this->_factory);
}

static void	freeTerminalList(const std::vector<ASymbol*> & terminalList)
{
	size_t	vector_size = 0;
	size_t	i = 0;

	vector_size = terminalList.size();
	while (i < vector_size)
	{
		delete (terminalList[i]);
		i++;
	}
}

std::vector<ASymbol*>	ALexer::tokenizeStr(const std::string & str) const 
{
	ASymbol*			terminal;
	std::vector<ASymbol*>	terminalList;
	size_t				i = 0;
	size_t				str_size = 0;

	str_size = str.size();
	while (i < str_size)
	{
		try
		{
			terminal = this->_factory->createTerminal(str.substr(i, str_size - i));
		}
		catch (const std::exception & e)
		{
			freeTerminalList(terminalList);
			throw (e);
		}
		catch (const Aparse_exception & e)
		{
			freeTerminalList(terminalList);
			throw (e);
		}
		terminalList.push_back(terminal);
		i += terminal->getSize();
	}
	return (terminalList);
}

