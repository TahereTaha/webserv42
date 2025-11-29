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

- [ ] web server
	- [x] read the arguments.
	- [x] parse the file.
		- [x] read the file.
		- [x] tokenize.
		- [x] parse.
		- [x] check.
		- [x] init.
	- [ ] set up the server.
		- [x] set the sockets for the socket manager.
		- [ ] set the servers for the server manager.
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

