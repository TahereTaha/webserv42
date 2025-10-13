- lexemes to parse
	- server
	- server_name
	- listen
	- client_max_body_size
	- error_page
	- location
	- return
	- root
	- auto_index
	- index
	- limit_exept
	- ;
	- {
	- }
	- white_space
	- text
	- number

- making the parser.
- [x] make the parse rules.
- [x] fix bugs.
- [x] refactor the code so that is has beter names and make it is more modular.
- [ ] write each simbol of the tree with the rules.
	- [x] make the server symbol.
	- [x] make all the server symbol directives.
		- [x] make server name.
		- [x] make listen.
		- [x] make client_max_body_size.
		- [x] make error_page
	- [x] make the location symbol.
	- [ ] make all the location symbol directives.
		- [ ] limit_exept.
		- [ ] make return.
		- [ ] make root.
		- [ ] autoindex.
		- [ ] inedex.
- [ ] make a check for each ast node.
- [ ] write the translator to the structure.

- making the checker.

- [ ] web server
	- [x] read the arguments.
	- [ ] parse the file.
		- [x] read the file.
		- [x] tokenize.
		- [ ] parse.
		- [ ] check.
		- [ ] init.
	- [ ] set up the server.
	- [ ] run the server.

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



