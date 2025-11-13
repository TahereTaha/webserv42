#pragma once

#include <string>
#include <vector>

//	this are only the character that don't fall in any other group like ptc encoded or such.
#define PCHAR ":@"

class Fragment
{
	private:
		std::string	_text;

		void	checkFragmentText(void);
	protected:
	public:
		Fragment(void);
		Fragment(std::string text);
		Fragment(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end);
		~Fragment(void);

		std::string	getText(void) const ;
};
