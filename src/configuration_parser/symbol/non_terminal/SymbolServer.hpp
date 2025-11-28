#pragma once

#include <vector>

#include <ATerminal.hpp>
#include <ANonTerminal.hpp>

#include <intermediate_representation.hpp>

#include <SymbolServerName.hpp>
#include <SymbolListen.hpp>
#include <SymbolClientMaxBodySize.hpp>
#include <SymbolErrorPage.hpp>
#include <SymbolLocation.hpp>

typedef enum
{
	SERVER_NAME,
	SERVER_LISTEN,
	SERVER_CLIENT_MAX_BODY_SIZE,
	SERVER_ERROR_PAGE,
	SERVER_LOCATION,
}	t_server_directives;

class SymbolServer : public ANonTerminal
{
	private:
		t_server	_server;

		int			set_up_directive(AEvaluable *directive);
		
		int			set_up_directive_name(SymbolServerName *directive);
		int			set_up_directive_listen(SymbolListen *directive);
		int			set_up_directive_client_max_body_size(SymbolClientMaxBodySize *directive);
		int			set_up_directive_error_page(SymbolErrorPage *directive);
		int			set_up_directive_location(SymbolLocation *directive);
	protected:
	public:
		SymbolServer(void);
		~SymbolServer(void);

		const char		*what(void) const;
		SymbolServer	*clone(void) const;
		void			evaluate(Tree<AEvaluable*> *self);

		AParser	*getParser(void) const;
		t_server	getServer(void) const ;
};
