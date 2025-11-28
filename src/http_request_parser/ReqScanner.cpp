/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqScanner.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:02:01 by capapes           #+#    #+#             */
/*   Updated: 2025/11/28 15:52:15 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReqScanner.hpp"
#include "Schemas.hpp"

ReqScanner::ReqScanner(const std::string& raw)
	: _raw(raw), _pos(0) {}

#define LEADING 1
#define TRAILING 1 << 1
#define OPTIONAL_SPACES (LEADING | TRAILING)
#define SPACES " \t\n\r\f\v"

std::string trim(std::string& str, int flags, size_t start, size_t end)
{
	size_t length = end - start;
	
	if (flags | LEADING)
		start = str.find_first_not_of(SPACES, start, length);
    if (start == std::string::npos)
        return ("");
	if (flags | TRAILING)
    	end = str.find_last_not_of(SPACES, end - 1, length) + 1;
    return (str.substr(start, end - start));
}


std::string ReqScanner::getField(const std::string& delimiter, int flags) {		
	
	size_t 			end;
	std::string 	field = "";
	
	if (_ended)
		return (field);
	
	end = delimiter == EOF
			? _raw.size()
			: _raw.find(delimiter, _pos);
					
	_ended = end == std::string::npos;
	if (_ended)
	   return (field);
	
	field = flags 
		? trim(_raw, flags, _pos, end) 
		: _raw.substr(_pos, end - _pos);				
	_pos = end + delimiter.size();
	return (field);
}




void printfield(const std::string& field, const std::string& expected)
{
	std::cout << (field == expected ? "PASS: " : "FAIL: ");
	std::cout << "'" << field << "'  (expected '" << expected << "')" << std::endl;
}

// TEST CASES [generated with ChatGPT]
void reqScannerTest()
{
	std::cout << "\n === EMPTY STRING TEST ===\n";
	{
		ReqScanner scanner("");
		std::string field = scanner.getField("\r\n", OPTIONAL_SPACES);
		printfield(field, "");
	}

	std::cout << "\n === EMPTY DELIMITER TEST===\n";
	{
		ReqScanner scanner("Some data here");
		std::string field = scanner.getField("", OPTIONAL_SPACES);
		printfield(field, "");
	}

	std::cout << "\n === EMPTY FIELD AND DELIMITER===\n";
	{
		ReqScanner scanner("");
		std::string field = scanner.getField("", OPTIONAL_SPACES);
		printfield(field, "");
	}

	std::cout << "\n=== BASIC TRIM TESTS ===\n";
	{
		ReqScanner scanner("   Hello World   \r\nThis is a test string.\r\n\r\n");
		std::string field1 = scanner.getField("\r\n", OPTIONAL_SPACES);
		std::string field2 = scanner.getField("\r\n\r\n", OPTIONAL_SPACES);
		printfield(field1, "Hello World");
		printfield(field2, "This is a test string.");
	}

	std::cout << "\n=== NO-TRIM TESTS ===\n";

	{
		ReqScanner scanner2("NoSpacesHere\r\nAnotherLine.  \r\n");
		std::string field3 = scanner2.getField("\r\n", 0);
		std::string field4 = scanner2.getField("\r\n", 0);
		printfield(field3, "NoSpacesHere");
		printfield(field4, "AnotherLine.  ");
	}

	std::cout << "\n=== LEADING / TRAILING ONLY ===\n";

	{
		ReqScanner s("   LeadingOnly   \r\n   TrailingOnly   \r\n");
		std::string f1 = s.getField("\r\n", LEADING);
		std::string f2 = s.getField("\r\n", TRAILING);

		printfield(f1, "LeadingOnly   ");
		printfield(f2, "   TrailingOnly");
	}

	std::cout << "\n=== EMPTY FIELD TESTS ===\n";

	{
		ReqScanner s("\r\nA\r\n\r\nB\r\n");
		std::string f1 = s.getField("\r\n", OPTIONAL_SPACES);
		std::string f2 = s.getField("\r\n", OPTIONAL_SPACES);
		std::string f3 = s.getField("\r\n", OPTIONAL_SPACES);
		std::string f4 = s.getField("\r\n", OPTIONAL_SPACES);

		printfield(f1, "");  // empty line
		printfield(f2, "A");
		printfield(f3, "");  // empty line
		printfield(f4, "B");
	}

	std::cout << "\n=== MULTIPLE DELIMITER TESTS ===\n";

	{
		ReqScanner s("A--B----C--D");
		std::string f1 = s.getField("--", 0);
		std::string f2 = s.getField("----", 0);
		std::string f3 = s.getField("--", 0);

		printfield(f1, "A");
		printfield(f2, "B");
		printfield(f3, "C");
	}

	std::cout << "\n=== NO MATCHING DELIMITER ===\n";

	{
		ReqScanner s("HelloWorld");
		std::string f = s.getField("\r\n", OPTIONAL_SPACES);
		std::string f2 = s.getField("\r\n", OPTIONAL_SPACES);
		printfield(f, "");
		printfield(f2, "");
	}

	std::cout << "\n=== MIXED WHITESPACE ===\n";

	{
		ReqScanner s("\t  Mixed \t Spaces \n\nDone");
		std::string f1 = s.getField("\n", OPTIONAL_SPACES);
		std::string f2 = s.getField("\n", OPTIONAL_SPACES);

		printfield(f1, "Mixed \t Spaces");
		printfield(f2, "Done");
	}

	std::cout << "\n=== DELIMITER AT START ===\n";

	{
		ReqScanner s("\nABC\nDEF");
		std::string f1 = s.getField("\n", OPTIONAL_SPACES);
		std::string f2 = s.getField("\n", OPTIONAL_SPACES);
		std::string f3 = s.getField("\n", OPTIONAL_SPACES);

		printfield(f1, "");
		printfield(f2, "ABC");
		printfield(f3, "DEF");
	}

	std::cout << "\n=== DELIMITER AT END ===\n";

	{
		ReqScanner s("XYZ\n");
		std::string f1 = s.getField("\n", OPTIONAL_SPACES);
		std::string f2 = s.getField("\n", OPTIONAL_SPACES);

		printfield(f1, "XYZ");
		printfield(f2, "");
	}

	std::cout << "\n=== LONG STRING WITH MULTIPLE SPACING VARIATIONS ===\n";

	{
		ReqScanner s("   Alpha  \r\n Beta\t\t \r\n\tGamma   \r\n");
		std::string f1 = s.getField("\r\n", OPTIONAL_SPACES);
		std::string f2 = s.getField("\r\n", OPTIONAL_SPACES);
		std::string f3 = s.getField("\r\n", OPTIONAL_SPACES);

		printfield(f1, "Alpha");
		printfield(f2, "Beta");
		printfield(f3, "Gamma");
	}
}



// if (!flags)
// 		return (field);
		
// 	if (flags | LEADING)
// 		start = ignore_spaces(start, LEADING);
// 	if (flags | TRAILING)
// 		end = ignore_spaces(end, TRAILING);
// 	if (start == -1 || end == -1 || start == end)
// 		return ("");
// 	return (field.substr(start, end - start));


// Previous get field function 

// std::string remove_trailing(const std::string& str, const std::string& chars = " \t\r\n")
// {
//     size_t end = str.find_last_not_of(chars);
//     if (end == std::string::npos)
//         return "";
//     return str.substr(0, end + 1);
// }

// std::string remove_leading(const std::string& str, const std::string& chars = " \t\r\n")
// {
//     size_t start = str.find_first_not_of(chars);
//     if (start == std::string::npos)
//         return "";
//     return str.substr(start);
// }

// inline std::string getField(size_t& pos,
//                             const std::string& raw,
//                             const std::string& delimiter,
//                             bool optionalSpaces = false)
// {
//     size_t endPos = raw.find(delimiter, pos);

//     if (endPos == std::string::npos)
//         return ("");
//     if (delimiter == EOL)
//         endPos = raw.size();
//     std::string field = raw.substr(pos, endPos - pos);
//     pos = endPos + delimiter.size();
//     if (optionalSpaces)
//     {
//         field = remove_leading(field);
//         field = remove_trailing(field);
//     }

//     return field;
// }