#include "Point.hpp"

Point::Point(void)
{
	this->_text = "";
}

Point::Point(std::string str)
{
	setText(str);
}

Point::Point(const Point& other)
{
	*this = other;
}

Point& Point::operator=(const Point& other)
{
	if (this != &other)
	{
		this->_text = other._text;
	}
	return *this;
}

Symbol* Point::clone() const
{
	return new Point(*this);
}

void Point::setText(const std::string& str)
{
	if (!str.empty() && str[0] == '.')
		this->_text = ".";
	else
		this->_text = "";
}
