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















