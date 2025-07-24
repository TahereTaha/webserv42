#include <ATerminalFactory.hpp>
#include <stddef.h>
#include <parse_exception.hpp>

ATerminalFactory::ATerminalFactory(void)
{
}

ATerminalFactory::~ATerminalFactory(void)
{
	size_t	vector_size = 0;
	size_t	i = 0;

	vector_size = this->terminals.size();
	while (i < vector_size)
	{
		delete (this->terminals[i]);
		i++;
	}
}

void ATerminalFactory::addTerminalToFactory(ATerminal * terminal)
{
	terminals.push_back(terminal);
}

ATerminal*	ATerminalFactory::createTerminal(const std::string & str)
{
	size_t		terminal_size = 0;
	ATerminal*	match = NULL;
	ATerminal*	new_terminal = NULL;
	
	//	find the match
	{
		size_t	i = 0;
		size_t	vector_size = 0;
		size_t	terminal_current_size = 0;

		vector_size = this->terminals.size();
		while (i < vector_size)
		{
			terminal_current_size = this->terminals[i]->getTerminalSizeOnStr(str);
			if (terminal_current_size > terminal_size)
			{
				terminal_size = terminal_current_size;
				match = this->terminals[i];
			}
			i++;
		}
		if (terminal_size == 0)
		{
			parse_exception	e(UNRECOGNIZE_CHARACTER);
			e.setLine(this->_line);
			e.setColumn(this->_column);
			e.setSize(0);
			throw (e);
		}
	}

	//	make a new terminal
	{
		std::string	text;

		text = str.substr(0, terminal_size);
		new_terminal = dynamic_cast<ATerminal *>(match->clone());
		new_terminal->setText(text);
		new_terminal->setLine(this->_line);
		new_terminal->setColumn(this->_column);
		new_terminal->setSize(terminal_size);

		this->updateIndex(text);
	}
	return (new_terminal);
}

void	ATerminalFactory::updateIndex(const std::string & str)
{
	char	*c_str = (char *) str.c_str();
	size_t	i = 0;

	while (c_str[i])
	{
		if (c_str[i] == '\n')
		{
			this->_line++;
			this->_column = 0;
		}
		else
			this->_column++;
		i++;
	}
}

void	ATerminalFactory::resetIndex(void)
{
	this->_line = 0;
	this->_column = 0;
}
