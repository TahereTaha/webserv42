# webserv42

A 42 School project implementing a HTTP web server in C++98.

The goal of this project is to understand how web servers work internally: sockets, HTTP request parsing, configuration files, routing rules, file descriptors, non-blocking I/O, and server response handling.

---

## What this project shows

* HTTP server implementation in C++98
* Socket setup and server listening flow
* Event-driven connection handling with epoll
* HTTP request parsing
* HTTP response generation
* Configuration file parsing
* URI parsing and path handling
* Multiple server/location configuration structure
* Error handling with custom exceptions
* Makefile-based C++ build workflow
* Systems programming concepts applied to web infrastructure

---

## Tech stack

* C++98
* Unix sockets
* epoll
* HTTP
* Makefile

---

## How it works

The server reads a configuration file, parses the server/location rules, sets up the required sockets, and starts handling incoming HTTP connections.

Basic flow:

```text
Configuration file
        ↓
Lexer / parser
        ↓
Server configuration
        ↓
Socket setup
        ↓
Connection manager
        ↓
Request parsing
        ↓
Response handling
```

---

## Usage

Clone the repository:

```bash
git clone git@github.com:TahereTaha/webserv42.git
cd webserv42
```

Build the project:

```bash
make
```

Run the server with a configuration file:

```bash
./webserv docs/server.conf
```

Run the test target:

```bash
make test
```

Clean object files:

```bash
make clean
```

Remove object files and the binary:

```bash
make fclean
```

Rebuild from scratch:

```bash
make re
```

---

## Project structure

```text
.
├── docs/                  # Example configuration files and documentation
├── inc/                   # Header files
├── src/                   # Server source code
│   ├── Server/            # Server and response handling
│   ├── URI_parsing/       # URI parsing logic
│   ├── configuration_parser/
│   ├── connection_manager/
│   ├── exceptions/
│   └── http_request_parser/
├── test/                  # Test files and test configuration
├── Makefile
└── setup.sh
```

---

## Main concepts practiced

### HTTP server behavior

The project explores how a server receives requests, parses them, and returns valid HTTP responses.

### Configuration parsing

The server is configured through `.conf` files with server and location blocks, similar in spirit to common web server configuration formats.

### Non-blocking connections

Connection handling is organized around an event-driven model using epoll, allowing the server to manage multiple connections efficiently.

### URI and request parsing

The project includes custom parsing logic for HTTP requests and URI components, which helps build a deeper understanding of how web requests are structured.

### C++98 architecture

Because the project follows C++98 constraints, the code relies on manual design decisions, custom structures, clear ownership, and careful error handling.

---

## Why this project matters

`webserv42` is a systems programming project that connects low-level programming with web development.

It helps build practical understanding of concepts that are useful in backend and full-stack development:

* How HTTP works under the hood
* How servers manage sockets and clients
* How configuration-driven applications are structured
* How requests are parsed and transformed into responses
* How infrastructure tools like Nginx are conceptually built
* How to design larger C++ projects with multiple modules

---

## Repository topics

Suggested GitHub topics:

```text
cpp
cpp98
http-server
web-server
sockets
epoll
systems-programming
network-programming
http
makefile
42-school
42-project
``` 
