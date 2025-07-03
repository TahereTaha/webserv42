#pragma once

#include <iostream>
#include "Terminal.hpp"

class Number : public Terminal
{
	private:
	protected:
	public:
		Number(void);
		Number(std::string str);
		Number(const Number& other);
		Number& operator=(const Number& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};
