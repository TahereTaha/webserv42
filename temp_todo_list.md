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

- [x] evaluate the locations.
	- [x] set up the route of this location.
		- [x] init the route.
			- [x] set the location path.
			- [x] set the return.
			- [x] set the root.
			- [x] set the autoindex.
			- [x] set the index.
			- [x] set the limit except.
	- [x] set up the route of all sub locations.

- [ ] make a check for each ast node.
	- [x] make the code on the configuration parser.
		- [x] fix the errors on the tree container.
	- [x] add some printing functions to debug the analysis.
		- [x] add printig of the tree nodes id.
		- [x] add functions to print each struct of the IR.
	- [x] make location.
		- [x] make make the return.
		- [x] make root.
		- [x] make autoindex.
		- [x] make index.
		- [x] make limit exept.
	- [ ] make server.
		- [ ] make server name.
		- [ ] make listen.
		- [ ] make client max body size.
		- [ ] make error page.
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

