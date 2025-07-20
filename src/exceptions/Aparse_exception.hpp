#pragma once

#include <string>

//	format of a error mesage 

//	error type
//	place
//	tips

//	some suporting types and global variables.
typedef enum
{
	UNDEFINED_ERROR,
	UNRECOGNIZE_CHARACTER,
	UNCLOSED_QUOTE,
}	t_parse_errno;

class Aparse_exception
{
	private:
	protected:
		t_parse_errno	_errorType;

		std::string		_errorMsg;
		const char	*strerror(void) const ;
		Aparse_exception(t_parse_errno type);
	public:
		virtual ~Aparse_exception(void);

		virtual	void	makeErrorMsg(void) = 0;
		std::string		what(void) const ;
		
		t_parse_errno	getErrorType(void) const ;
		void			setErrorType(t_parse_errno newType);
};

