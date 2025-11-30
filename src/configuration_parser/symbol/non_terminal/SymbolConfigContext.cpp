#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolConfigContext.hpp>

#include <SymbolServer.hpp>


#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

#include <defines.hpp>

SymbolConfigContext::SymbolConfigContext(void)
{
}

SymbolConfigContext::~SymbolConfigContext(void)
{
}

const char	*SymbolConfigContext::what(void) const
{
	return ("configuration context");
}

SymbolConfigContext	*SymbolConfigContext::clone(void) const 
{
	return (new SymbolConfigContext(*this));
}

#include <IR_printing_functions.hpp>

void		SymbolConfigContext::evaluate(Tree<AEvaluable*> *self)
{
	size_t	i = 0;
	while (i < self->getChildNodeSize())
	{
		this->_servers.push_back(dynamic_cast<SymbolServer *>(self->getChildNode(i)->getContent())->getServer());
		i++;
	}

	if (!DEBUG_PRINT)
		return ;
	i = 0;
	while (i < this->_servers.size())
	{
		printServer(this->_servers[i]);
		i++;
	}
}

AParser	*SymbolConfigContext::getParser(void) const
{
	AParsingRule	*rule = new ParsingRuleRepetition(1, -1, \
			new ParsingRuleSymbol(SymbolServer().clone()));
	return (new AParser(this->clone(), rule));
}

std::vector<t_server>	SymbolConfigContext::getServers(void) const 
{
	return (this->_servers);
}

