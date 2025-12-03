/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqScanner.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:02:01 by capapes           #+#    #+#             */
/*   Updated: 2025/12/01 18:39:56 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReqScanner.hpp"
#include "Schemas.hpp"

#define LEADING 1
#define TRAILING 2
#define OPTIONAL_SPACES 3
#define NOT_FOUND std::string::npos

ReqScanner::ReqScanner()
	: _raw(""), _pos(0), _ended(false) {
	_size = 0;
}

ReqScanner::ReqScanner(const std::string& raw)
	: _raw(raw), _pos(0), _ended(false) {
	_size = _raw.size();
	if (_size == 0)
		_pos = NOT_FOUND;
}

ReqScanner::~ReqScanner() {}

void ReqScanner::append(const std::string& raw) {
	if (isEndPos())
		_pos = 0;
	_raw.append(raw);
	_size = _raw.size();
}

size_t ReqScanner::getEndPos(const std::string& delimiter)
{
	size_t res;

	delimiter == EOF_ 
		? res = _size
		: res = _raw.find(delimiter, _pos);

	return res;
}

inline bool ReqScanner::isEndPos()
{
	return (_pos == NOT_FOUND || _pos >= _size);
}

// TODO: remove optionalSpaces from class
std::string ReqScanner::getField(const std::string& delimiter) 
{		
	if (isEndPos())
		return EMPTY_STRING;	

	size_t		start 	= _pos;
	size_t		end		= getEndPos(delimiter);
	std::string field 	= EMPTY_STRING; 

	if (end != NOT_FOUND && end != start)
		field = _raw.substr(start, end - start);
	_pos = end + delimiter.size();
	return field;
}


bool	ReqScanner::get_ended()
{
	return isEndPos();
}


// // TODO: redo tests for ReqScanner
// void printfield(const std::string& field, const std::string& expected)
// {
// 	std::cout << (field == expected ? "PASS: " : "FAIL: ");
// 	std::cout << "'" << field << "'  (expected '" << expected << "')" << std::endl;
// }

// // TEST CASES [generated with ChatGPT]
// void reqScannerTest()
// {
// 	std::cout << "\n === EMPTY STRING TEST ===\n";
// 	{
// 		ReqScanner scanner("");
// 		std::string field = scanner.getField("\r\n", OPTIONAL_SPACES);
// 		printfield(field, "");
// 	}

// 	std::cout << "\n === EMPTY DELIMITER TEST===\n";
// 	{
// 		ReqScanner scanner("Some data here");
// 		std::string field = scanner.getField(EOF_, OPTIONAL_SPACES);
// 		printfield(field, "Some data here");
// 	}

// 	std::cout << "\n === EMPTY FIELD AND DELIMITER===\n";
// 	{
// 		ReqScanner scanner("");
// 		std::string field = scanner.getField("", OPTIONAL_SPACES);
// 		printfield(field, "");
// 	}

// 	std::cout << "\n=== BASIC TRIM TESTS ===\n";
// 	{
// 		ReqScanner scanner("   Hello World   \r\nThis is a test string.\r\n\r\n");
// 		std::string field1 = scanner.getField("\r\n", OPTIONAL_SPACES);
// 		std::string field2 = scanner.getField("\r\n\r\n", OPTIONAL_SPACES);
// 		printfield(field1, "Hello World");
// 		printfield(field2, "This is a test string.");
// 	}

// 	std::cout << "\n=== NO-TRIM TESTS ===\n";

// 	{
// 		ReqScanner scanner2("NoSpacesHere\r\nAnotherLine.  \r\n");
// 		std::string field3 = scanner2.getField("\r\n", 0);
// 		std::string field4 = scanner2.getField("\r\n", 0);
// 		printfield(field3, "NoSpacesHere");
// 		printfield(field4, "AnotherLine.  ");
// 	}

// 	std::cout << "\n=== LEADING / TRAILING ONLY ===\n";

// 	{
// 		ReqScanner s("   LeadingOnly   \r\n   TrailingOnly   \r\n");
// 		std::string f1 = s.getField("\r\n", LEADING);
// 		std::string f2 = s.getField("\r\n", TRAILING);

// 		printfield(f1, "LeadingOnly   ");
// 		printfield(f2, "   TrailingOnly");
// 	}

// 	std::cout << "\n=== EMPTY FIELD TESTS ===\n";

// 	{
// 		ReqScanner s("\r\nA\r\n\r\nB\r\n");
// 		std::string f1 = s.getField("\r\n", OPTIONAL_SPACES);
// 		std::string f2 = s.getField("\r\n", OPTIONAL_SPACES);
// 		std::string f3 = s.getField("\r\n", OPTIONAL_SPACES);
// 		std::string f4 = s.getField("\r\n", OPTIONAL_SPACES);

// 		printfield(f1, "");  // empty line
// 		printfield(f2, "A");
// 		printfield(f3, "");  // empty line
// 		printfield(f4, "B");
// 	}

// 	std::cout << "\n=== MULTIPLE DELIMITER TESTS ===\n";

// 	{
// 		ReqScanner s("A--B----C--D");
// 		std::string f1 = s.getField("--", 0);
// 		std::string f2 = s.getField("----", 0);
// 		std::string f3 = s.getField("--", 0);

// 		printfield(f1, "A");
// 		printfield(f2, "B");
// 		printfield(f3, "C");
// 	}

// 	std::cout << "\n=== NO MATCHING DELIMITER ===\n";

// 	{
// 		ReqScanner s("HelloWorld");
// 		std::string f = s.getField("\r\n", OPTIONAL_SPACES);
// 		std::string f2 = s.getField("\r\n", OPTIONAL_SPACES);
// 		printfield(f, "");
// 		printfield(f2, "");
// 	}

// 	std::cout << "\n=== MIXED WHITESPACE ===\n";

// 	{
// 		ReqScanner s("\t  Mixed \t Spaces \n\nDone");
// 		std::string f1 = s.getField("\n\n", OPTIONAL_SPACES);
// 		std::string f2 = s.getField("", OPTIONAL_SPACES);

// 		printfield(f1, "Mixed \t Spaces");
// 		printfield(f2, "Done");
// 	}

// 	std::cout << "\n=== DELIMITER AT START ===\n";

// 	{
// 		ReqScanner s("\nABC\nDEF");
// 		std::string f1 = s.getField("\n", OPTIONAL_SPACES);
// 		std::string f2 = s.getField("\n", OPTIONAL_SPACES);
// 		std::string f3 = s.getField("", OPTIONAL_SPACES);

// 		printfield(f1, "");
// 		printfield(f2, "ABC");
// 		printfield(f3, "DEF");
// 	}

// 	std::cout << "\n=== DELIMITER AT END ===\n";

// 	{
// 		ReqScanner s("XYZ\n");
// 		std::string f1 = s.getField("\n", OPTIONAL_SPACES);
// 		std::string f2 = s.getField("\n", OPTIONAL_SPACES);

// 		printfield(f1, "XYZ");
// 		printfield(f2, "");
// 	}

// 	std::cout << "\n=== LONG STRING WITH MULTIPLE SPACING VARIATIONS ===\n";

// 	{
// 		ReqScanner s("   Alpha  \r\n Beta\t\t \r\n\tGamma   \r\n");
// 		std::string f1 = s.getField("\r\n", OPTIONAL_SPACES);
// 		std::string f2 = s.getField("\r\n", OPTIONAL_SPACES);
// 		std::string f3 = s.getField("\r\n", OPTIONAL_SPACES);

// 		printfield(f1, "Alpha");
// 		printfield(f2, "Beta");
// 		printfield(f3, "Gamma");
// 	}
// }