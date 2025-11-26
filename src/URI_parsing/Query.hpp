#pragma once

#include <string>
#include <vector>

//	this are only the character that don't fall in any other group like ptc encoded or such.
#define PCHAR ":@"

class Query
{
	private:
		std::string	_text;

		void	checkQueryText(void);
	protected:
	public:
		Query(void);
		Query(std::string text);
		Query(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end);
		~Query(void);

		std::string	getText(void) const ;
};
