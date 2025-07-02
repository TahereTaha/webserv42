#pragma once

#include "Terminal.hpp"

class Point : public Terminal
{
	private:
	protected:
	public:
		Point(void);
		Point(std::string str);
		Point(const Point& other);
		Point& operator=(const Point& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};

