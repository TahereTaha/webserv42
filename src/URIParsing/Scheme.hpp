#pragma once

#include <string>
#include <vector>

typedef enum
{
	scheme_FILE = 0,
	scheme_FTP,
	scheme_HTTP,
	scheme_HTTPS,
	scheme_MAILTO,
	scheme_TEL,
	scheme_IMAP,
	scheme_IRC,
	scheme_NNTP,
	scheme_ACAP,
	scheme_ICAP,
	scheme_MTQP,
	scheme_WSS,
	scheme_UNOFFICIAL,
}	t_uri_scheme;

class Scheme
{
	private:
		std::string		_text;
		t_uri_scheme	_scheme;

		void	normalizeText(void);

		// in case of not being correct it will throw.
		void	checkSchemeTextValid(void) const ;

		void	setScheme(void);
	protected:
	public:
		Scheme(void);
		Scheme(std::string text);
		//	this asumes that it is called by the URI class.
		//	and that the tokens are separated by the gen_delims.
		Scheme(std::vector<std::string>::iterator &iter, std::vector<std::string>::iterator end);
		~Scheme(void);

		t_uri_scheme	getSchemeType(void) const ;
};

int		operator == (const t_uri_scheme &scheme_1, const Scheme &scheme_2);
int		operator == (const Scheme &scheme_1, const t_uri_scheme &scheme_2);

int		operator != (const t_uri_scheme &scheme_1, const Scheme &scheme_2);
int		operator != (const Scheme &scheme_1, const t_uri_scheme &scheme_2);

//int	operator == 

