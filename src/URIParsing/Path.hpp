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

		std::vector<std::string>	getSections(void) const;
		std::string					getPathText(void) const;

		bool	operator == (const Path &rhs) const ;
	
		//		in case of the path not being a prefix a negative is returned.
		//		in case of it being a prefix a number is returned being all the extra segments that
		//	the path has over the prefix. this number can be zero denoting the same path.
		int		is_prefix(const Path &prefix_path) const ;

		//	for debuging purposes.
		void	print(void) const;
};
