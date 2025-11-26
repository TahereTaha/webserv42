#pragma once

#include <vector>
#include <string>

std::vector<std::string>	tokenize(std::string text, std::string delimiters);

void						print_tokens(std::vector<std::string> tokens);

