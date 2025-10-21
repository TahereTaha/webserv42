#pragma once

#include <string>
#include <>

class malformed_pct_encoding : public std::invalid_argument
{
	public:
		malformed_pct_encoding(const string &msg) : std::invalid_argument(msg) {}
};

//	any malformed pct_encoding will be throw as exeptions.
std::string	decode_pct_encoded_string(std::string text);

std::string	encode_to_pct_encoding(std::string text, std::string reserved_chars = "");

