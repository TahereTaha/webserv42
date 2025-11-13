#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include <Scheme.hpp>
#include <Authority.hpp>
#include <Path.hpp>
#include <Query.hpp>
#include <Fragment.hpp>

//					":/?@"
#define gen_delims	":/?#[]@"
#define sub_delims	"!$&'()*+,;="
#define reserved	gen_delims sub_delims

//	this contains to all the alnum characters.
#define UNRESERVED "-._~"

//	this uri is made with the sole purpose of handeling http uris.
//	using this class with other kinds of uri will result in undefined behevor.

typedef enum
{
	FULL_FORM = 0,
	NETWORK_PATH,
	ABSOLUTE_PATH,
	RELATIVE_PATH,
}	t_reference_type;

class URI
{
	private:
		std::string	_text;	//	the uri in a string format.
		std::vector<std::string>	_tokens;

		t_reference_type	_type;

		void	identifyURIType(void);

		int			_isSchemeSet;
		Scheme		_scheme;
		int			_isAuthoritySet;
		Authority	_authority;
		//	the path will allways be set even if it is empty.
		Path		_path;
		int			_isQuerySet;
		Query		_query;
		int			_isFragmentSet;
		Fragment	_fragment;

//		void	checkSchemeSpecificSyntax(void);
	public:
		//	this is guaranteed to throw if the text falls outside of the scope of uri.
		//	and it will throw if 
		URI(std::string uri);
		~URI();

		Scheme		&getScheme(void);
		Authority	&getAuthority(void);
		Path		&getPath(void);
		Query		&getQuery(void);
		Fragment	&getFragment(void);
};

