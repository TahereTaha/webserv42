#!/usr/bin/env python3
import cgi
import os
import cgitb
import sys

cgitb.enable()

UPLOAD_DIR = "/tmp/http_server/files"  # ensure this exists

def send_response(status_code="200 OK", body=""):
    body_bytes = body.encode("utf-8")
    content_length = len(body_bytes)

    # Send a full HTTP response
    print(f"HTTP/1.1 {status_code}")
    print("Content-Type: text/html; charset=utf-8")
    print(f"Content-Length: {content_length}")
    print("Connection: close")
    print()
    print(body, end="")

# ------------------------------------------------------------
# DEBUG RAW STDIN INPUT
# ------------------------------------------------------------
raw = sys.stdin.buffer.read()

with open("/tmp/cgi_raw.log", "wb") as f:
    f.write(raw)

# Reset stdin so FieldStorage can parse from the raw buffer
sys.stdin = open('/tmp/cgi_raw.log', 'rb')

# ------------------------------------------------------------
# PARSE MULTIPART
# ------------------------------------------------------------
form = cgi.FieldStorage()

# Debug info
with open("/tmp/cgi_debug.log", "a") as log:
    log.write("---- NEW REQUEST ----\n")
    log.write(f"CONTENT_LENGTH={os.environ.get('CONTENT_LENGTH')}\n")
    log.write(f"CONTENT_TYPE={os.environ.get('CONTENT_TYPE')}\n")
    log.write(f"REQUEST_METHOD={os.environ.get('REQUEST_METHOD')}\n")
    log.write(f"RAW_SIZE={len(raw)}\n")
    log.write(f"Form keys: {list(form.keys())}\n")
    if "file" in form:
        log.write(f"Filename: {form['file'].filename}\n")
    else:
        log.write("No 'file' field received.\n")

# ------------------------------------------------------------
# HANDLE FILE
# ------------------------------------------------------------
file_item = form["file"] if "file" in form else None

if file_item and file_item.filename:
    filename = os.path.basename(file_item.filename)
    save_path = os.path.join(UPLOAD_DIR, filename)

    try:
        with open(save_path, "wb") as f:
            f.write(file_item.file.read())

        body = f"""<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Upload successful</title></head>
<body>
  <h2>Upload successful!</h2>
  <p>Saved as: <code>{save_path}</code></p>
</body>
</html>"""

        send_response("200 OK", body)

    except Exception as e:
        send_response("500 Internal Server Error",
f"""<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Server error</title></head>
<body>
  <h2>Internal Server Error</h2>
  <p>{e}</p>
</body>
</html>""")

else:
    send_response("400 Bad Request",
"""<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Bad request</title></head>
<body>
  <h2>No file uploaded!</h2>
  <p>Please choose a file and try again.</p>
</body>
</html>""")
