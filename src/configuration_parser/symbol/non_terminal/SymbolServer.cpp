#include <ATerminal.hpp>
#include <ANonTerminal.hpp>
#include <SymbolServer.hpp>

#include <KeyWordServer.hpp>
#include <KeyLeftCurlyBracket.hpp>
#include <KeyRightCurlyBracket.hpp>
#include <Number.hpp>

#include <AParser.hpp>
#include <AParsingRule.hpp>
#include <ParsingRuleSymbol.hpp>
#include <ParsingRuleAnd.hpp>

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

void		SymbolServer::evaluate(Tree<AEvaluable*> *self)
{
	(void) self;
}

//	little test class
class test_class : public ANonTerminal
{
	public:
		test_class(void) {}
		~test_class(void) {}

		const char	*what(void) const {return ("test_class");}
		test_class	*clone(void) const {return (new test_class(*this));}
		void		evaluate(Tree<AEvaluable*> *self) {(void)self;}

		AParser	*getParser(void) const {
			AParsingRule	*rule =	new ParsingRuleSymbol(KeyWordServer().clone());
			return (new AParser(this->clone(), rule));
		}
};

AParser	*SymbolServer::getParser(void) const
{
//	AParsingRule	*rule =	new ParsingRuleSymbol(KeyWordServer().clone());
//	AParsingRule	*rule =	new ParsingRuleSymbol(Number().clone());
//	AParsingRule	*rule =	new ParsingRuleSymbol(test_class().clone());
	AParsingRule	*rule =	new ParsingRuleAnd(\
			new ParsingRuleSymbol(KeyWordServer().clone()),\
			new ParsingRuleSymbol(KeyLeftCurlyBracket().clone()),\
			new ParsingRuleSymbol(Number().clone()),\
			new ParsingRuleSymbol(Number().clone()),\
			new ParsingRuleSymbol(KeyRightCurlyBracket().clone()),\
			NULL);
	
	return (new AParser(this->clone(), rule));
}

