#pragma once

#include <string>
#include <vector>

//	the character that can be on a path are the:
//		- unreserved
//		- ptc encoded
//		- sub delims
//		- :
//		- @

//	this are only the character that don't fall in any other group like ptc encoded or such.
#define PCHAR ":@"

class Path
{
	private:
		std::string					_text;
		std::vector<std::string>	_sections;

		void	check_correct_path(void);
		void	fill_sections(void);
		void	normalize_path(void);
	protected:
	public:
		Path(void);
		Path(std::string);
		Path(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end);
		~Path(void);

		std::string	getText(void) const;
};
