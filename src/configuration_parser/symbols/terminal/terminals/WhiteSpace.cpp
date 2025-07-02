#include "WhiteSpace.hpp"
#include <cstring>

WhiteSpace::WhiteSpace(void)
{
    this->_text = "";
}

WhiteSpace::WhiteSpace(std::string str)
{
    setText(str);
}

WhiteSpace::WhiteSpace(const WhiteSpace& other)
{
    *this = other;
}

WhiteSpace& WhiteSpace::operator=(const WhiteSpace& other)
{
    if (this != &other)
    {
        this->_text = other._text;
    }
    return *this;
}

Symbol* WhiteSpace::clone() const
{
    return new WhiteSpace(*this);
}

void WhiteSpace::setText(const std::string& str)
{
    int i = 0;
    
    std::string::const_iterator it = str.begin();
    while (it != str.end() && strchr("\n\t \r", *it))
    {
        i++;
        it++;
    }
    this->_text = str.substr(0, i);
}
