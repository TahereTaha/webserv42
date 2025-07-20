- [ ] finish the parsing for the config file.
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

- [ ] add scaning to the parser.
	- [ ] go through each line and run the lexer on it.
	- [ ] remove 

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
			- [x] base class.
				- [ ] add a strerror_parse_exepiton
				- [x] types
					- [ ] unrecognise character.
					- [ ] unclosed quote.
					- [ ] multi_error.
			- [ ] parse exeption.
				- [ ] make error msg type.
				- [ ] make error msg place.
				- [ ] make error msg tip.
				- [ ] make error msg.
		- [ ] error please provide only a config file.
	- [ ] set up the server.



error msg 1:
- error kind
- place
- visual aid
- tips




























