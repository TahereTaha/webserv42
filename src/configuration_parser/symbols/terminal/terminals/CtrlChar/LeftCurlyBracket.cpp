#include "LeftCurlyBracket.hpp"

LeftCurlyBracket::LeftCurlyBracket(void)
{
    this->_text = "";
}

LeftCurlyBracket::LeftCurlyBracket(std::string str)
{
    setText(str);
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

Symbol* LeftCurlyBracket::clone() const
{
    return new LeftCurlyBracket(*this);
}

void LeftCurlyBracket::setText(const std::string& str)
{
    if (!str.empty() && str[0] == '{')
        this->_text = "{";
    else
        this->_text = "";
}
