#include <ConfigFileTerminalFactory.hpp>

#include <KeyWordServer.hpp>
#include <KeyWordServerName.hpp>
#include <KeyWordListen.hpp>
#include <KeyWordClientMaxBodySize.hpp>
#include <KeyWordErrorPage.hpp>
#include <KeyWordLocation.hpp>
#include <KeyWordReturn.hpp>
#include <KeyWordLimitExept.hpp>
#include <KeyWordRoot.hpp>
#include <KeyWordAutoIndex.hpp>
#include <KeyWordIndex.hpp>

#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>
#include <KeySemicolon.hpp>

#include <TextConfigFile.hpp>
#include <Number.hpp>

#include <WhiteSpace.hpp>

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
	this->addTerminalToFactory(new KeyWordLimitExept());
	this->addTerminalToFactory(new KeyWordRoot());
	this->addTerminalToFactory(new KeyWordAutoIndex());
	this->addTerminalToFactory(new KeyWordIndex());
	
	this->addTerminalToFactory(new KeyLeftCurlyBracket());
	this->addTerminalToFactory(new KeyRightCurlyBracket());
	this->addTerminalToFactory(new KeySemicolon());
	
	this->addTerminalToFactory(new Number());
	this->addTerminalToFactory(new TextConfigFile());
	
	this->addTerminalToFactory(new WhiteSpace());
}

