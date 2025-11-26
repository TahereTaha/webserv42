#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolLocation.hpp>

#include <KeyWordLocation.hpp>
#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>
#include <Number.hpp>
#include <TextConfigFile.hpp>

#include <SymbolLocation.hpp>
#include <SymbolLimitExcept.hpp>
#include <SymbolReturn.hpp>
#include <SymbolRoot.hpp>
#include <SymbolAutoIndex.hpp>
#include <SymbolIndex.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>
#include <ParsingRuleOr.hpp>
#include <ParsingRuleRepetition.hpp>

#include <Path.hpp>

SymbolLocation::SymbolLocation(void)
{
}

SymbolLocation::~SymbolLocation(void)
{
}

const char	*SymbolLocation::what(void) const
{
	return ("location_symbol");
}

SymbolLocation	*SymbolLocation::clone(void) const 
{
	return (new SymbolLocation(*this));
}

static int	identify_directive(AEvaluable* directive)
{
	if (dynamic_cast<SymbolReturn *>(directive))
		return (LOCATION_RETURN);
	if (dynamic_cast<SymbolRoot *>(directive))
		return (LOCATION_ROOT);
	if (dynamic_cast<SymbolIndex *>(directive))
		return (LOCATION_INDEX);
	if (dynamic_cast<SymbolAutoIndex *>(directive))
		return (LOCATION_AUTOINDEX);
	if (dynamic_cast<SymbolLimitExcept *>(directive))
		return (LOCATION_LIMITEXCEPT);
	if (dynamic_cast<SymbolLocation *>(directive))
		return (LOCATION_SUBLOCATION);
	return (LOCATION_SUBLOCATION);
}

void	SymbolLocation::set_up_location_directive_limitexcept(SymbolLimitExcept *directive)
{
	this->_routes[0].default_response.accepted_methods = directive->getMethods();
}

void	SymbolLocation::set_up_location_directive_autoindex(SymbolAutoIndex *directive)
{
	this->_routes[0].default_response.directory_listing_enabled = directive->getIsSet();
}

void	SymbolLocation::set_up_location_directive_index(SymbolIndex *directive)
{
	if (directive->getIndexFiles().size() == 0)
		this->_routes[0].default_response.index_file = "";
	else
		this->_routes[0].default_response.index_file = (directive->getIndexFiles())[0];
}

void	SymbolLocation::set_up_location_directive_root(SymbolRoot *directive)
{
	this->_routes[0].default_response.root = directive->getPath();
}

void	SymbolLocation::set_up_location_directive_return(SymbolReturn *directive)
{
	this->_routes[0].response_type = STATIC;
	this->_routes[0].static_response.status_code = directive->getStatusCode();
	this->_routes[0].static_response.text = directive->getBodyText();
}

int		SymbolLocation::set_up_location_directive(AEvaluable* directive)
{
	if (dynamic_cast<SymbolReturn *>(directive))
		set_up_location_directive_return(dynamic_cast<SymbolReturn *>(directive));
	if (dynamic_cast<SymbolRoot *>(directive))
		set_up_location_directive_root(dynamic_cast<SymbolRoot *>(directive));
	if (dynamic_cast<SymbolIndex *>(directive))
		set_up_location_directive_index(dynamic_cast<SymbolIndex *>(directive));
	if (dynamic_cast<SymbolAutoIndex *>(directive))
		set_up_location_directive_autoindex(dynamic_cast<SymbolAutoIndex *>(directive));
	if (dynamic_cast<SymbolLimitExcept *>(directive))
		set_up_location_directive_limitexcept(dynamic_cast<SymbolLimitExcept *>(directive));

	return (identify_directive(directive));
}


int		SymbolLocation::set_up_location(Tree<AEvaluable*> *self)
{

	//	seting up the uri
	{
		TextConfigFile	*path_symbol = dynamic_cast<TextConfigFile *>(self->getChildNode(0)->getContent());
		Path	path(path_symbol->getText());
		this->_routes[0].uri = path.getPathText();
	}

	//	seting the rest of fields.
	int	bit_field_set_directives = 0;

	size_t	i = 1;
	while (i < self->getChildNodeSize())
	{
		int	location_directive = set_up_location_directive(self->getChildNode(i)->getContent());
		if (location_directive != LOCATION_SUBLOCATION  && \
			((1 << location_directive) & bit_field_set_directives))
			throw (std::invalid_argument("location redeclared directive."));
		bit_field_set_directives |= 1 << location_directive;
		i++;
	}
	return (bit_field_set_directives);
}

void	SymbolLocation::set_route_defaults(void)
{
	t_route	route;

	route.response_type = DEFAULT;
	route.default_response.root = "/data/www/";
	route.default_response.directory_listing_enabled = 1;
	route.default_response.index_file = "index.html";
	route.default_response.accepted_methods.push_back(GET);
	route.default_response.accepted_methods.push_back(POST);
	route.default_response.accepted_methods.push_back(DELETE);
	
	this->_routes.push_back(route);
}

template <typename T>
static std::vector<T>	concat_vectors(std::vector<T> vec, std::vector<T> append)
{
	size_t	i = 0;
	while (i < append.size())
	{
		vec.push_back(append[i]);
		i++;
	}
	return (vec);
}

static std::vector<t_route>	get_all_child_routes(Tree<AEvaluable*> *self)
{
	std::vector<t_route> routes;

	size_t	i = 0;
	while (i < self->getChildNodeSize())
	{
		SymbolLocation	*location = dynamic_cast<SymbolLocation *>(self->getChildNode(i)->getContent());
		if (location)
			routes = concat_vectors(routes, location->getRoutes());
		i++;
	}
	return (routes);
}

static std::vector<int>	get_all_child_bit_fields(Tree<AEvaluable*> *self)
{
	std::vector<int> bit_fields;

	size_t	i = 0;
	while (i < self->getChildNodeSize())
	{
		SymbolLocation	*location = dynamic_cast<SymbolLocation *>(self->getChildNode(i)->getContent());
		if (location)
			bit_fields = concat_vectors(bit_fields, location->getBitFieldsSetDirectives());
		i++;
	}
	return (bit_fields);
}

static void	make_children_inherit(t_route parent_route, int parent_bit_field, t_route &route, \
		int bit_field)
{
	if (parent_route.uri != "/")
		route.uri = parent_route.uri + route.uri;
	if (((1 > LOCATION_ROOT) & parent_bit_field) && !((1 > LOCATION_ROOT) & bit_field))
		route.default_response.root = parent_route.default_response.root;
	if (((1 > LOCATION_INDEX) & parent_bit_field) && !((1 > LOCATION_INDEX) & bit_field))
		route.default_response.index_file = parent_route.default_response.index_file;
	if (((1 > LOCATION_AUTOINDEX) & parent_bit_field) && !((1 > LOCATION_AUTOINDEX) & bit_field))
		route.default_response.directory_listing_enabled = parent_route.default_response.directory_listing_enabled;
	if (((1 > LOCATION_LIMITEXCEPT) & parent_bit_field) && !((1 > LOCATION_LIMITEXCEPT) & bit_field))
		route.default_response.accepted_methods = parent_route.default_response.accepted_methods;
}

static std::vector<t_route>	set_up_child_routes(Tree<AEvaluable*> *self, t_route parent, \
		int bit_field)
{
	std::vector<t_route>	routes;
	std::vector<int>		bit_fields;

	routes = get_all_child_routes(self);
	bit_fields = get_all_child_bit_fields(self);
	
	size_t	i = 0;
	while (i < routes.size())
	{
		make_children_inherit(parent, bit_field, routes[i], bit_fields[i]);
		i++;
	}
	return (routes);
}

void		SymbolLocation::evaluate(Tree<AEvaluable*> *self)
{
	set_route_defaults();

	int	bit_field_set_directives = set_up_location(self);
	this->_bit_fields_set_directives.push_back(bit_field_set_directives);

	std::vector<t_route>	child_routes;
	child_routes = set_up_child_routes(self, this->_routes[0], bit_field_set_directives);
	std::vector<int> bit_fields = get_all_child_bit_fields(self);

	this->_routes = concat_vectors(this->_routes, child_routes);
	this->_bit_fields_set_directives = concat_vectors(this->_bit_fields_set_directives, bit_fields);

//	std::cout << "patata.\n\n\n" << std::endl;
//	size_t i = 0;
//	while (i < this->_routes.size())
//	{
//		printRoute(this->_routes[i]);
//		i++;
//	}
}

AParser	*SymbolLocation::getParser(void) const
{
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordLocation().clone()),\
			new ParsingRuleSymbol(TextConfigFile().clone()),\
			new ParsingRuleSymbol(KeyLeftCurlyBracket().clone()),\
			new ParsingRuleRepetition(1, -1, new ParsingRuleOr(\
				new ParsingRuleSymbol(SymbolLimitExcept().clone()),\
				new ParsingRuleSymbol(SymbolReturn().clone()),\
				new ParsingRuleSymbol(SymbolRoot().clone()),\
				new ParsingRuleSymbol(SymbolAutoIndex().clone()),\
				new ParsingRuleSymbol(SymbolIndex().clone()),\
				new ParsingRuleSymbol(SymbolLocation().clone()),\
				NULL)),\
			new ParsingRuleSymbol(KeyRightCurlyBracket().clone()),\
			NULL);
	return (new AParser(this->clone(), rule));
}

std::vector<t_route>	SymbolLocation::getRoutes(void) const
{
	return (this->_routes);
}

std::vector<int>		SymbolLocation::getBitFieldsSetDirectives(void) const
{
	return (this->_bit_fields_set_directives);
}
