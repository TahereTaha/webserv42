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


- [ ] parse.
	- [x] make the tree compile with the tree container.
	- [ ] parse each token.
		- [	] manage the server directive.
			- [x] read that it starts with a server keyword.
			- [ ] check that it starts with a '{'.
			- [ ] check that it ends with a '}'.
			- [ ] try to generate any subtrees of the directives that are inside the server.
			- [ ] consume all the server directives with the "{...}".
	- [ ] make the semantic analysis.
		- [ ] go botom up checking that all the information is correct (analyze each node).


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







