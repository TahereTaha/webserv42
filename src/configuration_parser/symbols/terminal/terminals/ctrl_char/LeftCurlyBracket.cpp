#include "LeftCurlyBracket.hpp"

LeftCurlyBracket::LeftCurlyBracket(void)
{
    this->_text = "";
}

LeftCurlyBracket::LeftCurlyBracket(std::string str)
{
    if (!str.empty() && str[0] == '{')
        this->_text = "{";
    else
        this->_text = "";
}

LeftCurlyBracket::LeftCurlyBracket(const LeftCurlyBracket& other)
{
    *this = other;
}

LeftCurlyBracket& LeftCurlyBracket::operator=(const LeftCurlyBracket& other)
{
    if (this != &other)
    {
        this->_text = other._text;
    }
    return *this;
}
