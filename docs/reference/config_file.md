# configuration file structure.

the configuration file is formed by directives whitch define the behavior of
the http server or servers. Directives are divided into simple directives and
block directives. simple directives are formed by a name and parrameter
separeted by white space and terminated by a semicolon. block directves are
formed by a name and more directives housed by curly brackets. this directives are 

# directives.

- `server`
- `server_name`
- `listen`
- `error_page`
- `client_max_body_size`
- `location`
- `return`
- `methods_allowed`
- `root`
- `auto_inedx`
- `index`

## `server`

sets the configuration of the server a virtual server.

takes the form of:
	`
		server
		{
			directive1 ;
			directive2 ;
			directive3 ;
			...
		}
	`

## `server_name`

belongs in the server context. sets the name of the server. whitch will be used
to match the host header field with the correct server.

takes the form of a list of servernames:
	`server_name myweb.com ... ;`

## `listen`

belongs in a server context. sets the diferent ips+port that it connects to.

can take the form of just the ip, just the port, the ip and port or a list
of those. both ipv4 and ipv6 are suported:
	`listen ip;`
	`listen port;`
	`listen ip:port;`
	`listen ip ip port ip:port ... ;`

## `error_page`

belongs in the server context. sets the response body to be returned on
diferent errors.

takes the form of an error code with a file.
	`error_page ERROR_CODE 404.html`

## `client_max_body_size`

belongs in the server context. sets the maximum size that the server will
accept on a request. if the client exeds the configured size the error 413 
(Request Entry Too Large) is returned. if zero is set then the server will
accept any request regardles of the size of its body. by default this is set
to 1MB.

takes the form of a size.
	`client_max_body_size 0;`
	`client_max_body_size 16KB;`

## `location`

belongs in the server context or the location context. it is a block directive
containg more directives inside of its context. it configures the diferent
paths of the server. it can be nested in itself, the path is just apended to
the parents path.

takes the form of a path and a block with more directives.
	`
		location /path/to/somewhere/
		{
			directive1 arg;
			directive2 arg;
			directive3 arg;
			location /in/here/
			{
				directive1 arg;
				directive2 arg;
				directive3 arg;
			}
		}
	`

## `methods_allowed`

belongs in the location context. it will define all the methods that the
current location will accept. by default if it is not defined it will inherit
it from any parent location and if any is avaliable it will accept all methods.

takes the form of a list of allowed methos;
	`methods_allowed get post head;`

## `return`

belongs in the location context. it will define the response overwriting the
default response. in the case of 301, 302, 303, 307, and 308 responce codes it
will use the text in the location header variable location instead of the body.
it is not inherited with nested locations.

takes the form of a responce code with some text.
	`return 302 http://google.com`
	`return 404 "no page found."`

## `root`

belongs in the location context. sets the file or folder to serve to the 
client. it is inherited on nested locations. there is no default it is
mandatory to have one.

takes the form of a path.
	`root /data/www;`

## `auto_index`

belongs in the location context. allows or not to acces files and folders
inside the location. it is inherited on nested locations. the default is to 
allow acces.

takes the form of a "yes" or a "no".
	`auto_index yes;`
	`auto_index no;`

## `index`

belongs in the location context. sets a default file to serve when accesing a 
folder on the location. it is inherited on nested locations. the default is index.html

it takes the form of a list of files.
	`index index.html main.html index.php main.php;`


