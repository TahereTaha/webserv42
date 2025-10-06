#pragma once

#include <string>
#include <stddef.h>
#include <vector>
#include <string>

//	some suporting types.
typedef enum
{
	NO_ERROR,
	UNRECOGNIZE_CHARACTER,
	UNCLOSED_QUOTE,
	UNRECOGNIZED_SYMBOL,
	UNDEFINED_ERROR,
}	t_parse_errno;

//	these are the difirent promotions that are posible:
//		unrecognize character -> unclosed quote.
//

class parse_exception
{
	private:
		t_parse_errno	_errorType;

		std::string		_errorMsg;
		size_t		_line;
		size_t		_column;
		size_t		_size;

		const char	*strerror(void) const ;
	protected:
	public:
		parse_exception(t_parse_errno type);
		~parse_exception(void);

		void	tryPromote(std::string line);	// promote unrecognized characters.
		void	makeErrorMsg(	const std::string & fileName, \
								const std::vector<std::string> & fileContent);
		std::string		what(void) const ;

		void	setLine(size_t line);
		void	setColumn(size_t column);
		void	setSize(size_t size);
		size_t	getLine(void) const ;
		size_t	getColumn(void) const ;
		size_t	getSize(void) const ;
};
