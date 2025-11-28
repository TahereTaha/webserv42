#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolListen.hpp>

#include <KeyWordListen.hpp>
#include <TextConfigFile.hpp>
#include <KeySemicolon.hpp>

#include <SymbolListen.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

#include <cstring>
#include <Authority.hpp>

SymbolListen::SymbolListen(void)
{
}

SymbolListen::~SymbolListen(void)
{
}

const char	*SymbolListen::what(void) const
{
	return ("listen_symbol");
}

SymbolListen	*SymbolListen::clone(void) const 
{
	return (new SymbolListen(*this));
}


void		SymbolListen::evaluate(Tree<AEvaluable*> *self)
{
	TextConfigFile		*text;
	struct sockaddr_storage	socket;
	std::vector<struct sockaddr*>	socket_arr;

	size_t i = 0;
	while (i < self->getChildNodeSize())
	{
		text = dynamic_cast<TextConfigFile *>(self->getChildNode(i)->getContent());
		Authority	authority;
		if (text->getText()[0] != ':')
			authority = Authority(text->getText());
		else
			authority = Authority(std::string("127.0.0.1") + text->getText());
		socket_arr = authority.getSockaddr();
		size_t j = 0;
		while (j < socket_arr.size())
		{
			if (socket_arr[j]->sa_family == AF_INET)
				std::memmove(&socket, socket_arr[j], sizeof(struct sockaddr_in));
			else
				std::memmove(&socket, socket_arr[j], sizeof(struct sockaddr_in6));
			this->_sockets.push_back(socket);
			j++;
		}
		i++;
	}

}

AParser	*SymbolListen::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordListen().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleSymbol(TextConfigFile().clone())),\
			new ParsingRuleSymbol(KeySemicolon().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

std::vector<struct sockaddr_storage>	SymbolListen::getSockets(void) const
{
	return (this->_sockets);
}

