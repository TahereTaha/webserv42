#pragma once

#include "Terminal.hpp"

class LeftCurlyBracket : public Terminal
{
	private:
	protected:
	public:
		LeftCurlyBracket(void);
		LeftCurlyBracket(std::string str);
		LeftCurlyBracket(const LeftCurlyBracket& other);
		LeftCurlyBracket& operator=(const LeftCurlyBracket& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};
