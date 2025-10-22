#include <tokenize.hpp>

#include <vector>
#include <string>
#include <iostream>

std::vector<std::string>	tokenize(std::string text, std::string delimiters)
{
	size_t	start = 0;
	size_t	end = text.find_first_of(delimiters, start);
	if (end == start)
		end++;

	std::vector<std::string>	tokens;
	while (end < text.size())
	{
		tokens.push_back(text.substr(start, end - start));

		start = end;
		end = text.find_first_of(delimiters, start);
		if (end == start)
			end++;
	}
	tokens.push_back(text.substr(start, end - start));
	return (tokens);
}

void	print_tokens(std::vector<std::string> tokens)
{
	size_t	i= 0;
	while (i < tokens.size())
	{
		std::cout << tokens[i] << "\n";
		i++;
	}
	std::cout << std::flush;
}


