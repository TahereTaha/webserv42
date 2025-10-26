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

- [ ] make a reg name object.
- [ ] make a ip literal.
- [ ] make a ipv4 object.
- [ ] make a ipv6 object.

- [ ] parse the host.
	- [x] make the class.
	- [x] make the constructors.
	- [ ] make a geter for the type.

- [ ] parse the authority.
	- [x] make a class that will hold all the parts.
	- [x] get all the needed info from the from the input.
	- [x]  separete out the tokenizer logic from the URI class.
	- [x] make the user info.
	- [ ] make the host.
	- [ ] make the port.

- [x] make percent encoder and decoder.
- [x] make a simple tokenization for the uri.
- [x] parse the scheme.
- [ ] parse the authority.
	- [ ] parse the user info.
	- [ ] parse the host.
		- [ ] parse the ip.
		- [ ] parse the host name.
	- [ ] parse the port.
- [ ] parse the path.
- [ ] parse the query.
- [ ] parse the fragment.
- [ ] check scheme specific syntax.

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

