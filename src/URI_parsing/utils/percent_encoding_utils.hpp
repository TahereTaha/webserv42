#pragma once

#include <string>
#include <stdexcept>

class malformed_pct_encoding : public std::invalid_argument
{
	public:
		malformed_pct_encoding(const std::string &msg) : std::invalid_argument(msg) {}
};

int	is_pct_encoded(std::string text);
//	any malformed pct_encoding will be throw as exeptions.
std::string	decode_pct_encoded_string(std::string text);

//	the reserved chars are characters from the isgraf group that can't apear on the encoded string.
std::string	encode_to_pct_encoding(std::string text, std::string reserved_chars = "");

