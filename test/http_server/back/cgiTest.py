#!/usr/bin/env python3
body = "Hello from CGI"

print("HTTP/1.1 200 Success")
print("Content-Length: {}".format(len(body) + 1))
print("Connection: close")
print()
print(body)