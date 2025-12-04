#!/usr/bin/env python3
import sys
import os

# Set up CGI environment variables
for key, value in os.environ.items():
    if key.startswith("HTTP_") or key in [
        "CONTENT_LENGTH",
        "CONTENT_TYPE",
        "GATEWAY_INTERFACE",
        "PATH_INFO",
        "QUERY_STRING",
        "REMOTE_ADDR",
        "REQUEST_METHOD",
        "SCRIPT_NAME",
        "SERVER_NAME",
        "SERVER_PORT",
        "SERVER_PROTOCOL",
        "SERVER_SOFTWARE"
    ]:
        os.environ[key] = value
# this cgi receives a POST request with a file as a multipart/form-data
UPLOAD_DIR = "/tmp/http_server/files"
if not os.path.exists(UPLOAD_DIR):
    os.makedirs(UPLOAD_DIR)
# parse the multipart/form-data
content_type = os.environ.get("CONTENT_TYPE", "")
boundary = content_type.split("boundary=")[-1].encode()
body = sys.stdin.buffer.read()
parts = body.split(b"--" + boundary)
for part in parts:
    if b'Content-Disposition' in part:
        headers, file_data = part.split(b"\r\n\r\n", 1)
        file_data = file_data.rsplit(b"\r\n", 1)[0]  # remove trailing \r\n
        disposition = headers.decode()
        if 'filename="' in disposition:
            filename = disposition.split('filename="')[1].split('"')[0]
            filepath = os.path.join(UPLOAD_DIR, filename)
            with open(filepath, "wb") as f:
                f.write(file_data)

# saves | create the file

# Send HTTP response
print("Status: 201 Created")
print("Content-Type: text/plain")
print()
print("File uploaded successfully.")  