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

- [ ] make a method to get the sockaddr structure.
	- [x] make the ip literals parse the correctly.
	- [ ] make a constructor of sockaddr_in and sockaddr_in6 on the ip literals.
	- [ ] make this constructor for the reg_names too with the getaddrinfo.

- [x] make percent encoder and decoder.
- [x] make a simple tokenization for the uri.
- [x] parse the scheme.
- [x] parse the authority.
	- [ ] make a method to get the sockaddr structure.
- [x] parse the path.
- [x] parse the query.
- [x] parse the fragment.



- [ ] make a check for each ast node.
	- [ ] make server name.
	- [ ] make listen.
	- [ ] 	first milestone.
	- [ ] make client max body size.
	- [ ] make error page.
	- [ ] 	second milestone.
	- [ ] make limit exept.
	- [ ] make make the return.
	- [ ] make root.
	- [ ] make autoindex.
	- [ ] make index.
	- [ ] 	third milestone.
	- [ ] make location.
	- [ ] make server.
- [ ] write the translator to the structure.

- making the checker.

- [ ] web server
	- [x] read the arguments.
	- [ ] parse the file.
		- [x] read the file.
		- [x] tokenize.
		- [x] parse.
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

