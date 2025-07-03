#pragma once

#include "Terminal.hpp"

class RightCurlyBracket : public Terminal
{
	private:
	protected:
	public:
		RightCurlyBracket(void);
		RightCurlyBracket(std::string str);
		RightCurlyBracket(const RightCurlyBracket& other);
		RightCurlyBracket& operator=(const RightCurlyBracket& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};

