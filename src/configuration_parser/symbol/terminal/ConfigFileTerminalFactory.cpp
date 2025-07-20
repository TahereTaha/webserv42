#include <ConfigFileTerminalFactory.hpp>

ConfigFileTerminalFactory::ConfigFileTerminalFactory(void)
{
	this->resetIndex();
	this->addTerminalToFactory(new KeyWordServer());
	this->addTerminalToFactory(new KeyWordServerName());
	this->addTerminalToFactory(new KeyWordListen());
	this->addTerminalToFactory(new KeyWordClientMaxBodySize());
	this->addTerminalToFactory(new KeyWordErrorPage());
	this->addTerminalToFactory(new KeyWordLocation());
	this->addTerminalToFactory(new KeyWordReturn());
	this->addTerminalToFactory(new KeyWordlimitExept());
	this->addTerminalToFactory(new KeyWordRoot());
	this->addTerminalToFactory(new KeyWordAutoIndex());
	this->addTerminalToFactory(new KeyWordIndex());
}

