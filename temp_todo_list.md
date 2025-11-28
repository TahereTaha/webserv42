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

- [ ] make the server symbol.
	- [x] class boiler plait.
	- [x] set up the listen.
	- [x] set up the client max body size.
	- [ ] add some simple error.

- [ ] make a check for each ast node.
	- [x] make location.
		- [x] make make the return.
		- [x] make root.
		- [x] make autoindex.
		- [x] make index.
		- [x] make limit exept.
	- [ ] make server.
		- [/] make server name.
		- [x] make listen.
		- [x] make client max body size.
		- [x] make error page.
- [ ] write the translator to the structure.

- [ ] web server
	- [x] read the arguments.
	- [ ] parse the file.
		- [x] read the file.
		- [x] tokenize.
		- [x] parse.
			- [x] change the target simbol to a server vector.
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

