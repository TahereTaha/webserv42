#!/usr/bin/env python3
import sys
import os

UPLOAD_DIR = "/tmp/http_server/files"
os.makedirs(UPLOAD_DIR, exist_ok=True)

content_type = os.environ.get("CONTENT_TYPE", "")
content_length = os.environ.get("CONTENT_LENGTH", "0")
method = os.environ.get("REQUEST_METHOD", "")

errors = []

# --- Validation ---
if method != "POST":
    errors.append("Only POST is accepted.")

if "multipart/form-data" not in content_type:
    errors.append("Invalid Content-Type (multipart/form-data required).")

if "boundary=" not in content_type:
    errors.append("Missing boundary in Content-Type.")

if errors:
    response = "HTTP/1.1 400 Bad Request\r\n"
    response += "Content-Type: text/plain\r\n\r\n"
    response += "\n".join(errors)
    sys.stdout.write(response)
    sys.exit(0)

boundary = content_type.split("boundary=")[-1].encode()

# Read entire body (raw multipart)
try:
    body = sys.stdin.buffer.read(int(content_length))
except Exception:
    sys.stdout.write(
        "HTTP/1.1 400 Bad Request\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Failed to read request body."
    )
    sys.exit(0)

if not body:
    sys.stdout.write(
        "HTTP/1.1 400 Bad Request\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Empty request body."
    )
    sys.exit(0)

# --- Parse multipart ---
parts = body.split(b"--" + boundary)

saved_filename = None

for part in parts:
    if b"Content-Disposition" not in part:
        continue

    if b"\r\n\r\n" not in part:
        continue

    headers, file_data = part.split(b"\r\n\r\n", 1)
    file_data = file_data.rstrip(b"\r\n")

    disposition = headers.decode(errors="ignore")

    if 'filename="' not in disposition:
        continue

    filename = disposition.split('filename="', 1)[1].split('"', 1)[0]
    if not filename:
        continue

    filepath = os.path.join(UPLOAD_DIR, filename)

    try:
        with open(filepath, "wb") as f:
            f.write(file_data)
        saved_filename = filename
    except Exception as e:
        sys.stdout.write(
            "HTTP/1.1 500 Internal Server Error\r\n"
            "Content-Type: text/plain\r\n\r\n"
            f"Error saving file: {e}"
        )
        sys.exit(0)

# --- Output full HTTP response ---
if saved_filename is None:
    sys.stdout.write(
        "HTTP/1.1 400 Bad Request\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "No file found in multipart data."
    )
else:
    sys.stdout.write(
        "HTTP/1.1 201 Created\r\n"
        "Content-Type: text/plain\r\n\r\n"
        f"Uploaded: {saved_filename}"
    )
