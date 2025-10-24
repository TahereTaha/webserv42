#include <URI.hpp>

#include <string>
#include <stdexcept>
#include <iostream>

#include <tokenize.hpp>
#include <Scheme.hpp>
#include <Authority.hpp>

URI::URI(std::string uri)
{
	this->_isSchemeSet = 0;
	this->_isAuthoritySet = 0;
	this->_text = uri;

	this->_tokens = tokenize(this->_text, gen_delims);
	if (this->_tokens.size() == 0)
		throw (std::invalid_argument("invalid uri"));
	print_tokens(this->_tokens);

	this->identifyURIType();

	//	parse the each the 5 components of the URI.
	std::vector<std::string>::iterator	iter = this->_tokens.begin();
//	std::vector<std::string>::iterator	check_point = iter;
	std::vector<std::string>::iterator	end = this->_tokens.end();

	if (this->_type == FULL_FORM)
	{
		this->_isSchemeSet = 1;
		this->_scheme = Scheme(iter, end);
		if (*iter != ":")
			throw (std::invalid_argument("invalid uri"));
		iter++;
	}

	if (this->_type <= NETWORK_PATH)
	{
		this->_isAuthoritySet = 1;
		this->_authority = Authority(iter, end);
	}

//	this->_path = Path(iter, end);
//
//	check_point = iter;
//	this->_query = Query(iter, end);
//	if (check_point != iter)
//		this->_isQuerySet = 1;
//
//	check_point = iter;
//	this->_fragment = Fragment(iter, end);
//	if (check_point != iter)
//		this->_isFargmentSet = 1;
//
//	if (iter != end)
//		throw (std::invalid_argument("invalid uri"));
//
//	this->checkSchemeSpecificSyntax().
}

URI::~URI()
{
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

Scheme		&URI::getScheme(void)
{
	if (!this->_isSchemeSet)
		throw (std::out_of_range("unset scheme"));
	return (this->_scheme);
}

Authority	&URI::getAuthority(void)
{
	if (!this->_isAuthoritySet)
		throw (std::out_of_range("unset authority"));
	return (this->_authority);
}

