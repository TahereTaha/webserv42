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

- [ ] add functions to print each struct of the IR.
		- [ ] print t_server.
			- [x] print the internal stuff.
				- [x] print the server_name.
				- [x] print the max_body_size.
			- [x] print the sockets.
				- [x] print one socket.
			- [ ] print the error pages.
				- [ ] print one error page.
			- [ ] print the routes.

- [ ] make a check for each ast node.
	- [x] make the code on the configuration parser.
		- [x] fix the errors on the tree container.
	- [ ] add some printing functions to debug the analysis.
		- [x] add printig of the tree nodes id.
		- [ ] add functions to print each struct of the IR.
	- [ ] make location.
		- [ ] make make the return.
		- [ ] make root.
		- [ ] make autoindex.
		- [ ] make index.
	- [ ] make server.
		- [ ] make server name.
		- [ ] make listen.
		- [ ] make client max body size.
		- [ ] make error page.
		- [ ] make limit exept.
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

