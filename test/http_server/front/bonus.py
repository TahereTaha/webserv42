#!/usr/bin/env python3
import os
import sys

# -------- Read theme cookie --------
cookies = os.environ.get("HTTP_COOKIE", "")
theme = "light"

if "theme=dark" in cookies:
    theme = "dark"
elif "theme=light" in cookies:
    theme = "light"

# -------- Define CSS for both themes --------

LIGHT_STYLE = """
<style>
  :root {
    --bg: #f5f5f5;
    --text: #333;
    --card: white;
    --accent: #4caf50;
    --accent-hover: #45a047;
    --border: #ccc;
  }
</style>
"""

DARK_STYLE = """
<style>
  :root {
    --bg: #1e1e1e;
    --text: #e0e0e0;
    --card: #2a2a2a;
    --accent: #8cff87;
    --accent-hover: #74ff6a;
    --border: #444;
  }
</style>
"""

# Pick active theme CSS
THEME_CSS = DARK_STYLE if theme == "dark" else LIGHT_STYLE


# -------- Shared CSS --------

SHARED_CSS = """
<style>
  body {
    font-family: Arial, sans-serif;
    background: var(--bg);
    margin: 0;
    padding: 20px;
    color: var(--text);
  }
  h2 {
    color: var(--text);
    border-left: 4px solid var(--accent);
    padding-left: 10px;
  }
  img {
    border-radius: 8px;
    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);
  }
  form {
    background: var(--card);
    padding: 15px;
    border-radius: 8px;
    box-shadow: 0 2px 6px rgba(0, 0, 0, 0.15);
    width: fit-content;
  }
  input[type="file"] {
    margin-bottom: 10px;
  }
  button {
    background: var(--accent);
    color: black;
    padding: 8px 12px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    transition: 0.2s;
  }
  button:hover {
    background: var(--accent-hover);
  }
  hr {
    border: none;
    border-bottom: 1px solid var(--border);
    margin: 25px 0;
  }
  .section {
    margin-bottom: 30px;
  }
  #themeSelect {
    background: var(--card);
    color: var(--text);
    border: 1px solid var(--border);
    padding: 5px;
    border-radius: 5px;
  }
</style>
"""


# -------- HTML Output --------

html = f"""<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Theme Test Page</title>

{THEME_CSS}
{SHARED_CSS}

<script>
  // Read cookie
  function getCookie(name) {{
    return document.cookie
      .split("; ")
      .find(row => row.startsWith(name + "="))
      ?.split("=")[1];
  }}

  let theme = getCookie("theme") || "light";
  document.documentElement.setAttribute("data-theme", theme);
</script>

</head>
<body>

<div class="section">
  <label for="themeSelect"><strong>Theme:</strong></label>
  <select id="themeSelect">
    <option value="light">Light</option>
    <option value="dark">Dark</option>
  </select>
</div>

<script>
  // Set dropdown
  document.getElementById("themeSelect").value = theme;

  // Change cookie + reload
  document.getElementById("themeSelect").addEventListener("change", (e) => {{
    let selected = e.target.value;
    document.cookie = "theme=" + selected + "; path=/; max-age=" + (60*60*24*30);
    window.location.reload();
  }});
</script>


<div class="section">
  <h2>Images in Another Folder</h2>
  <p>It is common to store images in a sub-folder.</p>
  <img src="img/taha.png" alt="HTML Icon" style="width:128px;height:128px;" />
</div>

<hr />

<div class="section">
  <h2>Upload & Send File (multipart/form-data)</h2>

  <form action="/files/cgiTest.py" method="POST" enctype="multipart/form-data">
    <input type="file" name="file" />
    <br />
    <button type="submit">Upload</button>
  </form>
</div>

<hr />

<div class="section">
  <h2>Test redirect to /rickrolll</h2>
  <button onclick="window.location.href='/rickrolll'">Go to /rickrolll</button>
</div>

</body>
</html>
"""

# -------- Output full HTTP response --------
sys.stdout.write("HTTP/1.1 200 OK\r\n")
sys.stdout.write("Content-Type: text/html\r\n\r\n")
sys.stdout.write(html)
