#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <vector>
#include <string>

class StringUtils
{
public:
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static int hexToDecimal(char hex);
};

#endif // STRING_UTILS_HPP
