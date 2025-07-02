#pragma once

#include <iostream>
#include "Terminal.hpp"

class Return : public Terminal
{
	private:
	protected:
	public:
		Return(void);
		Return(std::string str);
		Return(const Return& other);
		Return& operator=(const Return& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};

