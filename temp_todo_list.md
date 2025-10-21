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

- [x] build a percent encoder and decoder.
	- [x] decode.
	- [x] encode.

- [ ] prase the scheme
	- [x] make the text constructor.
	- [x] make the token constructor.
	- [ ] make a scheme normalizer.
	- [ ] check the scheme complies with the characters that it can have.
	- [ ] make the scheme recognizer.
	- [ ] make the overloading of ==.

- [ ] make percent encoder and decoder.
- [x] make a simple tokenization for the uri.
- [ ] parse the scheme.
- [ ] parse the authority.
	- [ ] parse the user info.
	- [ ] parse the host.
		- [ ] parse the ip.
		- [ ] parse the host name.
	- [ ] parse the port.
- [ ] parse the path.
- [ ] parse the query.
- [ ] parse the fragment.

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

