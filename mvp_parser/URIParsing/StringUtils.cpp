#include "StringUtils.hpp"

std::vector<std::string> StringUtils::split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == delimiter)
        {
            if (!token.empty())
                tokens.push_back(token);
            token.clear();
        }
        else
        {
            token += str[i];
        }
    }
    
    if (!token.empty())
        tokens.push_back(token);
    
    return tokens;
}

int StringUtils::hexToDecimal(char hex) 
{
    if (hex >= '0' && hex <= '9')
        return hex - '0';
    if (hex >= 'A' && hex <= 'F')
        return hex - 'A' + 10;
    if (hex >= 'a' && hex <= 'f')
        return hex - 'a' + 10;
    return -1;
}
