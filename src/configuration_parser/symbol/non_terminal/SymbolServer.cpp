#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolServer.hpp>

#include <KeyWordServer.hpp>
#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>
#include <Number.hpp>

#include <SymbolServerName.hpp>
#include <SymbolListen.hpp>
#include <SymbolClientMaxBodySize.hpp>
#include <SymbolErrorPage.hpp>
#include <SymbolLocation.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

SymbolServer::SymbolServer(void)
{
}

SymbolServer::~SymbolServer(void)
{
}

const char	*SymbolServer::what(void) const
{
	return ("server_symbol");
}

SymbolServer	*SymbolServer::clone(void) const 
{
	return (new SymbolServer(*this));
}

template <typename T>
static std::vector<T>	concat_vectors(std::vector<T> vec1, std::vector<T> vec2)
{
	size_t	i = 0;
	while (i < vec2.size())
	{
		vec1.push_back(vec2[i]);
		i++;
	}
	return (vec1);
}

int			SymbolServer::set_up_directive_location(SymbolLocation *directive)
{
	this->_server.route = concat_vectors(this->_server.route, directive->getRoutes());
	return (SERVER_LOCATION);
}

int			SymbolServer::set_up_directive_error_page(SymbolErrorPage *directive)
{
	this->_server.error_page = concat_vectors(this->_server.error_page, directive->getErrorPages());
	return (SERVER_ERROR_PAGE);
}

int			SymbolServer::set_up_directive_client_max_body_size(SymbolClientMaxBodySize *directive)
{
	this->_server.client_max_body_size = directive->getMaxBodySize();
	return (SERVER_CLIENT_MAX_BODY_SIZE);
}

int			SymbolServer::set_up_directive_listen(SymbolListen *directive)
{
	this->_server.socket = directive->getSockets();
	return (SERVER_LISTEN);
}

int			SymbolServer::set_up_directive_name(SymbolServerName *directive)
{
	(void)directive;
	return (SERVER_NAME);
}

int			SymbolServer::set_up_directive(AEvaluable *directive)
{
	if (dynamic_cast<SymbolServerName *>(directive))
		return (set_up_directive_name(dynamic_cast<SymbolServerName *>(directive)));
	if (dynamic_cast<SymbolListen *>(directive))
		return (set_up_directive_listen(dynamic_cast<SymbolListen *>(directive)));
	if (dynamic_cast<SymbolClientMaxBodySize *>(directive))
		return (set_up_directive_client_max_body_size(dynamic_cast<SymbolClientMaxBodySize *>(directive)));
	if (dynamic_cast<SymbolErrorPage *>(directive))
		return (set_up_directive_error_page(dynamic_cast<SymbolErrorPage *>(directive)));
	if (dynamic_cast<SymbolLocation *>(directive))
		return (set_up_directive_location(dynamic_cast<SymbolLocation *>(directive)));
	return (-1);
}

static	void	set_default_server(t_server &server)
{
	server.client_max_body_size = 1024;
}


void		SymbolServer::evaluate(Tree<AEvaluable*> *self)
{
	int	bit_field_directives = 0;

	set_default_server(this->_server);
	size_t	i = 0;
	while (i < self->getChildNodeSize())
	{
		int	directive_made = set_up_directive(self->getChildNode(i)->getContent());
		if (directive_made != SERVER_LOCATION && directive_made != SERVER_ERROR_PAGE && \
			(bit_field_directives & (1 << directive_made)))
			throw (std::invalid_argument("server redeclared directive."));
		bit_field_directives = bit_field_directives | (1 << directive_made);
		i++;
	}
	if (!(bit_field_directives & (1 << SERVER_LISTEN)) || !(bit_field_directives & (1 << SERVER_LOCATION)))
		throw (std::invalid_argument("server important directives unset."));

//	printServer(this->_server);
}

AParser	*SymbolServer::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordServer().clone()),\
			new ParsingRuleSymbol(KeyLeftCurlyBracket().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleOr(\
				new ParsingRuleSymbol(SymbolServerName().clone()),\
				new ParsingRuleSymbol(SymbolListen().clone()),\
				new ParsingRuleSymbol(SymbolClientMaxBodySize().clone()),\
				new ParsingRuleSymbol(SymbolErrorPage().clone()),\
				new ParsingRuleSymbol(SymbolLocation().clone()),\
				NULL)),\
			new ParsingRuleSymbol(KeyRightCurlyBracket().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

t_server	SymbolServer::getServer(void) const 
{
	return (this->_server);
}

