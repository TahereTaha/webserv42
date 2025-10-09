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
- [ ] make the parse rules.
	- [x] make the simbol rule.
		- [x] make it.
		- [x] test for terminals.
		- [x] test for evaluables.
		- [x] test for non terminal.
	- [x] make the add rule.
		- [ ] test it with no rules.
		- [ ] test it with multiple rules.
	- [ ] make the or rule.
	- [ ] make the repetition rule.
- [ ] refactor the code so that is has beter names and make it is more modular.
	- [ ] change the error handeling to be able to hadle just simple parse_exceptions.
	- [ ] change the name of confirurationParser to file parser. and make it more modular.
	- [ ] change the name of the parsing rules.
	- [ ] change how the lexer is organized in classes.
	- [ ] change the print ast to a beter formated one.
- [ ] write each simbol of the tree with the rules.
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



