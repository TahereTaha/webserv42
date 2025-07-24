- lexemes to parse.
	- server
	- server_name
	- listen
	- client_max_body_size
	- error_page
	- location
	- return
	- limit_exept
	- root
	- auto_index
	- index
	- ;
	- {
	- }
	- white_space
	- text
	- number

- [ ] make the parse error class.
	- [x] add methods for seting the row and colum and size.
	- [x] add method for promoting the error in case it is a character not recognized.
	- [x] add the make error msg
		- [x] make the display of the error type.
		- [x] make the error location.
		- [x] make the visual aid for the error location.
			- [x] print out line or lines.
				- [x] replace all tabs with 4 spaces.
				- [x] make a hiligter.
- [ ] give it a more coherent color scheme.
- [ ] make the multy error.

- [ ] make the multy error class.
	- [ ] add some other basic variables and methods.


- [x] make it compile
- [x] refactor some code.
	- [x] make all the keywords desendent from AKeyWord.
	- [x] move the clone to the tokens.
	- [ ] change error handeling making it return multi error in all cases.
		- [ ] erase the base class and just implement multi_parse_error and parse_error.
- [ ] check that it is tokenizing correctly.
	- [ ] add a method of what to all symbols.
	- [ ] add a debuging option for printing extra information on the parsing prosses.
		- [ ] show the file.
		- [ ] show the token list.
		- [ ] show the parse tree.
- [ ] fix errors.
	- [ ] the text is not geting the correct text with quotes.
- [ ] format beter the error msg.
- [ ] get on with the parser.

- [ ] web server
	- [x] read the arguments.
	- [ ] parse the file.
		- [x] read the file.
		- [ ] tokenize.
		- [ ] parse.
		- [ ] check
		- [ ] init.
	- [ ] make a solid error managment.
		- [x] set cool colors.
		- [ ] parse exception.
			- [x] types
				- [ ] unrecognise character.
				- [ ] unclosed quote.
		- [ ] multy parse exception.
	- [ ] set up the server.



error msg 1:
- error kind
- place
- visual aid
- tips










errors: 3
unclosed quote.
docs/configfile2.conf:16:10
	server_name "server_name ;
				^~~~~~~~~~~~~~~
tip: multy line quoted strings are not suported try to close it before the end of the line.















