#include <URI.hpp>
#include <string>
#include <stdexcept>
#include <iostream>

static void	print_tokens(std::vector<std::string> tokens);

URI::URI(std::string uri)
{
	this->_text = uri;

	this->tokenize();
	if (this->_tokens.size() == 0)
		throw (std::invalid_argument("invalid uri"));
	print_tokens(this->_tokens);

	this->identifyURIType();

	//	parse the each the 5 components of the URI.
	std::vector<std::string>::iterator	iter = this->_tokens.begin();
	std::vector<std::string>::iterator	end = this->_tokens.end();

	if (this->_type == FULL_FORM)
	{
		this->_scheme = Scheme(iter, end);
		if (*iter != ":")
			throw (std::invalid_argument("invalid uri"));
		iter++;
	}

	if (this->_type <= NETWORK_PATH)
	{
//		this->_authority = Authority(iter, end);
	}
//	this->_path = Path(iter, end);
//	this->_query = Query(iter, end);
//	this->_fragment = Fragment(iter, end);
//	this->checkSchemeSpecificSyntax().
}

URI::~URI()
{
}

void	URI::tokenize(void)
{
	size_t	start = 0;
	size_t	end = this->_text.find_first_of(gen_delims, start);
	if (end == start)
		end++;

	while (end < this->_text.size())
	{
		this->_tokens.push_back(this->_text.substr(start, end - start));

		start = end;
		end = this->_text.find_first_of(gen_delims, start);
		if (end == start)
			end++;
	}
	this->_tokens.push_back(this->_text.substr(start, end - start));
}

//	auxiliar function for debuging purposes.
static void	print_tokens(std::vector<std::string> tokens)
{
	size_t	i= 0;
	while (i < tokens.size())
	{
		std::cout << tokens[i] << "\n";
		i++;
	}
	std::cout << std::flush;
}

void	URI::identifyURIType(void)
{
	//	identify relative path reference.
	if (this->_tokens[0] != "/")
	{
		if (this->_tokens.size() == 1)
		{
			this->_type = RELATIVE_PATH;
			return ;
		}
		if (this->_tokens[1] != ":")
		{
			this->_type = RELATIVE_PATH;
			return ;
		}
	}
	//	identify absolute path reference.
	if (this->_tokens[0] == "/" && this->_tokens.size() > 1 && this->_tokens[1] != "/")
	{
		this->_type = ABSOLUTE_PATH;
		return ;
	}
	//	identify network path reference.
	if (this->_tokens[0] == "/" && this->_tokens.size() > 1 && this->_tokens[1] == "/")
	{
		this->_type = NETWORK_PATH;
		return ;
	}
	this->_type = FULL_FORM;
}

