#pragma once

#include <iostream>
#include "Terminal.hpp"

class Listen : public Terminal
{
	private:
	protected:
	public:
		Listen(void);
		Listen(std::string str);
		Listen(const Listen& other);
		Listen& operator=(const Listen& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};

