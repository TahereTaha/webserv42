#include <ConfigFileLexer.hpp>
#include <ConfigFileTerminalFactory.hpp>

ConfigFileLexer::ConfigFileLexer(void)
{
	this->_factory = new ConfigFileTerminalFactory();
}


