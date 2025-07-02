#pragma once

#include <string>
#include "../Symbol.hpp"
#include <cstring>
#include <iostream>

// teminal symbol interface
// protected = 
// 	_text			// text of the terminal symbol;
// 	_matching_fn	// function to match the terminal symbol in a string *needed at creation or 
// 					  	when the text is set*;
// public = 
// 	clone()			// clone the terminal symbol and return a pointer to a new instance;
// 	~Terminal()		// destructor of the terminal symbol;
// 	setText()		// set the text of the terminal symbol;
// 	getText()		// get the text of the terminal symbol;
// 	length()		// get the length of the text of the terminal symbol;

class Terminal : public Symbol
{
	private:
	protected:
		std::string _text;
		// int 		_match_fn(const std::string &src);
	public:
		Terminal();
	
		virtual 			~Terminal();
		virtual Terminal* 	clone () const = 0;
		virtual void		setText(const std::string &text) = 0;

		std::string 		getText() const { return _text; };
		int					length() const { return _text.length(); };
};


int 		get_match(const std::string &src, const std::string &pattern);
std::string get_pattern(const std::string &src, const std::string &pattern);
