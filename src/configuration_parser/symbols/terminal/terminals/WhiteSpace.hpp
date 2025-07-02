#pragma once

#include "Terminal.hpp"
#include <cstring>

class WhiteSpace : public Terminal
{
	private:
	protected:
	public:
		WhiteSpace(void);
		WhiteSpace(std::string str);
		WhiteSpace(const WhiteSpace& other);
		WhiteSpace& operator=(const WhiteSpace& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};

