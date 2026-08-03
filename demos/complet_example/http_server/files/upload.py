#!/usr/bin/env python3
import sys
import os
import time

UPLOAD_DIR = "/tmp/http_server/files/uploads"
os.makedirs(UPLOAD_DIR, exist_ok=True)

content_type = os.environ.get("CONTENT_TYPE", "")
content_length = os.environ.get("CONTENT_LENGTH", "0")
method = os.environ.get("REQUEST_METHOD", "")

errors = []

# --- Minimal inline CSS block ---
STYLE = """
<style>
  body {
    font-family: Arial, sans-serif;
    background: #f7f7f7;
    padding: 20px;
    color: #333;
  }
  h2 {
    color: #444;
    border-left: 4px solid #4caf50;
    padding-left: 10px;
  }
  a {
    color: #4caf50;
    text-decoration: none;
    font-weight: bold;
  }
  a:hover {
    text-decoration: underline;
  }
  ul {
    background: #fff;
    padding: 10px 15px;
    border-radius: 6px;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
  }
  p {
    margin-top: 12px;
  }
</style>
"""

# --- Validation ---
if method != "POST":
    errors.append("Only POST is accepted.")

if "multipart/form-data" not in content_type:
    errors.append("Invalid Content-Type (multipart/form-data required).")

if "boundary=" not in content_type:
    errors.append("Missing boundary in Content-Type.")

if errors:
    response = "HTTP/1.1 400 Bad Request\r\n"
    response += "Content-Type: text/html\r\n\r\n"
    response += STYLE
    response += "<h2>400 Bad Request</h2>\n<ul>"
    for e in errors:
        response += f"<li>{e}</li>"
    response += "</ul>"
    response += "<p><a href='/'>Back to Home</a></p>"
    sys.stdout.write(response)
    sys.exit(0)

boundary = content_type.split("boundary=")[-1].encode()

# --- SAFE request-body reading (fixes hangs) ---
try:
    # Convert content_length safely
    try:
        length = int(content_length)
    except:
        length = 0

    body = b""
    remaining = length

    # Read in chunks to avoid blocking forever
    while remaining > 0:
        chunk = sys.stdin.buffer.read(65536)
        if not chunk:
            break
        body += chunk
        remaining -= len(chunk)

except Exception:
    sys.stdout.write(
        "HTTP/1.1 400 Bad Request\r\n"
        "Content-Type: text/html\r\n\r\n"
        + STYLE +
        "<h2>400 Bad Request</h2><p>Failed to read request body.</p>"
        "<p><a href='/'>Back to Home</a></p>"
    )
    sys.exit(0)

if not body:
    sys.stdout.write(
        "HTTP/1.1 400 Bad Request\r\n"
        "Content-Type: text/html\r\n\r\n"
        + STYLE +
        "<h2>400 Bad Request</h2><p>Empty request body.</p>"
        "<p><a href='/'>Back to Home</a></p>"
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
            "Content-Type: text/html\r\n\r\n"
            + STYLE +
            f"<h2>500 Internal Server Error</h2><p>Error saving file: {e}</p>"
            "<p><a href='/'>Back to Home</a></p>"
        )
        sys.exit(0)

# --- Output full HTTP response ---
if saved_filename is None:
    sys.stdout.write(
        "HTTP/1.1 400 Bad Request\r\n"
        "Content-Type: text/html\r\n\r\n"
        + STYLE +
        "<h2>400 Bad Request</h2><p>No file found in multipart data.</p>"
        "<p><a href='/'>Back to Home</a></p>"
    )
else:
    file_url = f"/files/uploads/{saved_filename}"  # Public URL link

    sys.stdout.write(
        "HTTP/1.1 201 Created\r\n"
        "Content-Type: text/html\r\n\r\n"
        + STYLE +
        f"<h2>File Uploaded</h2>"
        f"<p>Uploaded: <strong>{saved_filename}</strong></p>"
        f"<p>Link: <a href='{file_url}' target='_blank'>{file_url}</a></p>"
        "<p><a href='/'>Back to Home</a></p>"
    )

sys.exit(0)
