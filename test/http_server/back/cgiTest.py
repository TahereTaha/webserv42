
#!/usr/bin/env python3
import cgi
import os
import cgitb

cgitb.enable()

UPLOAD_DIR = "/var/www/uploads"  # ensure this exists and is writable

def send_response(status_code="200 OK", body=""):
    # Build and send a full HTTP-like response from CGI
    body_bytes = body.encode("utf-8")
    content_length = len(body_bytes)

    # CGI sends headers only; the web server prepends "HTTP/1.1 200 OK"
    # But we include Status to control that.
    print(f"Status: {status_code}")
    print("Content-Type: text/html; charset=utf-8")
    print(f"Content-Length: {content_length}")
    print("Connection: close")
    print()  # end of headers
    # Now the body:
    print(body, end="")

form = cgi.FieldStorage()
file_item = form["file"] if "file" in form else None

if file_item and file_item.filename:
    filename = os.path.basename(file_item.filename)
    save_path = os.path.join(UPLOAD_DIR, filename)

    try:
        with open(save_path, "wb") as f:
            while True:
                chunk = file_item.file.read(100000)
                if not chunk:
                    break
                f.write(chunk)

        body = f"""<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Upload successful</title>
</head>
<body>
  <h2>Upload successful!</h2>
  <p>Saved as: <code>{save_path}</code></p>
</body>
</html>
"""
        send_response("200 OK", body)

    except Exception as e:
        body = f"""<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Server error</title>
</head>
<body>
  <h2>Internal Server Error asd</h2>
  <p>{e}</p>
</body>
</html>
"""
        send_response("500 Internal Server Error", body)

else:
    body = """<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Bad request</title>
</head>
<body>
  <h2>No file uploaded!</h2>
  <p>Please choose a file and try again.</p>
</body>
</html>
"""
    send_response("400 Bad Request", body)