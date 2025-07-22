#include <stddef.h>
#include <string>
#include <stdexept>

//	generic exeption for errors in the parsing.
class parse_error : public std::invalid_argument
{
	private:
		std::string	_errorMsgKind;
		std::string	_errorMsg;	//	this is formed by the error kind, error place, and error tips.
	protected:

		//	errorMsg construction.
		void	addErrorMsgKind(void)
		{
			this->_errorMsg += this->_errorMsgKind;
		}
		virtual void	addErrorMsgPlace(void) {};
		virtual void	addErrorMsgTips(void) {};

	public:
		void	appendFrontToErrorMsgKind(const std::string & msg)
		{
			this->_errorMsgKind = msg + this->_errorMsgKind;
		}
		void	appendBackToErrorMsgKind(const std::string & msg)
		{
			this->_errorMsgKind = this->_errorMsgKind + msg;
		}

		parse_error(void) : std::invalid_argument("")
		{
			this->_errorMsgKind = "";
		}
		parse_error(const std::string & kind) : std::invalid_argument("")
		{
			this->_errorMsgKind = kind;
		}

		void	constructErrorMsg(void)
		{
			this->_errorMsg = "";
			this->addErrorMsgKind();
			this->addErrorMsgPlace();
			this->addErrorMsgTips();
		}
		const char*		what(void)
		{
			return (this->_errorMsg.c_str());
		}
}

class incorrect_argument_count : public parse_error
{
	private:
		char	**argv;
	protected:
		void	addErrorMsgPlace(void) 
		{

		}
		void	addErrorMsgTips(void) {};
	public:
		incorrect_argument_count(void) : parse_error("incorrect argument count") {};


}

//
//class unrecognize_character : public parse_error
//{
//	private:
//		size_t		_lineNum;
//		size_t		_columnNum;
//		std::string	_lineStr;
//	protected:
//	public:
//		unrecognize_character(void) : parse_error("this character is not recognized"){};
//}
//
