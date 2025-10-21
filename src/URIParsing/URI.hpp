#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include <Scheme.hpp>

#define gen_delims ":/?#[]@"

//	this uri is made with the sole purpose of handeling http uris.
//	using this class with other kinds of uri will result in undefined behevor.

class URI
{
	private:
		std::string	_text;	//	the uri in a string format.
		std::vector<std::string>	_tokens;

		Scheme		_scheme;
//		Auchority	_authority;
//		Path		_path;
//		Query		_query;
//		Fragment	_fragment;

		void	tokenize(void);

	public:
		//	this is guaranteed to throw if the text falls outside of the scope of uri.
		//	and it will throw if 
		URI(std::string uri);
		~URI();
};

