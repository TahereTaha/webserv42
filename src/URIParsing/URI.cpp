#include <URI.hpp>
#include <string>
#include <stdexcept>
#include <iostream>


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

URI::URI(std::string uri)
{
	this->_text = uri;
	
	this->tokenize();
	print_tokens(this->_tokens);
	std::vector<std::string>::iterator	iter = this->_tokens.begin();
	std::vector<std::string>::iterator	end = this->_tokens.end();

	this->_scheme = Scheme(iter, end);
	if (*iter != ":")
		throw (std::invalid_argument("invalid uri"));
	iter++;

//	this->_authority = Authority(iter, end);
//	this->_path = Path(iter, end);
//	this->_query = Query(iter, end);
//	this->_fragment = Fragment(iter, end);
}

URI::~URI()
{
}

