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

- [ ] make the usfull functions.
	- [x] is in server body.
	- [/] generate server body subtree.
	- [x] is in location body.
	- [ ] generate location body subtree.

- [ ] generate the subtres on the server body.
	- [ ] build the diferent symbols of this.
		- [x] server_name.(easy)
		- [ ] listen.(medium)
			- [ ] socket.
				- [ ] ipv4
				- [ ] port
		- [ ] client_max_body_size.(easy)

- [ ] parse.
	- [x] make the tree compile with the tree container.
	- [ ] parse each token.
		- [	] manage the server directive.
			- [x] read that it starts with a server keyword.
			- [x] check that it starts with a '{'.
			- [x] check that it ends with a '}'.
			- [ ] try to generate any subtrees of the directives that are inside the server body.
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







