#pragma once

#include <iostream>
#include "Terminal.hpp"

class ErrorPage : public Terminal
{
	private:
	protected:
	public:
		ErrorPage(void);
		ErrorPage(std::string str);
		ErrorPage(const ErrorPage& other);
		ErrorPage& operator=(const ErrorPage& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};

