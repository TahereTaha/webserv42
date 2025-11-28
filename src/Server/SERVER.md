## Server Class 

The `Server` class is a server built from a `t_server` configuration. 
It accepts a `Request` and returns a `ServerResponse`.

It is responsible for:

- **Method validation** (`GET`, `POST`, `DELETE` only)
- **Body size limits** (based on `client_max_body_size`)
- **Route selection** (longest-prefix match on the request target)
- **URI → filesystem mapping** for default routes
- **Simple file operations** (GET, POST/upload, DELETE)
- **Error handling** with optional custom error pages

---

## Request Handling Flow

When `Server::handleRequest(const Request &request)` is called, it roughly does:

1. **Extract request data**

   - Reads `method` and `requestTarget` from the request’s `ControlData`.

2. **Validate HTTP method**

   - If the method is not `GET`, `POST`, or `DELETE`, it returns a  
     `405 Method Not Allowed` response.

3. **Check POST body size**

   - If the method is `POST` and the body size exceeds `client_max_body_size`
     from the server configuration, it returns `413 Payload Too Large`.

4. **Select the best route**

   - Iterates over all configured routes.
   - Picks the route whose `uri` is the **longest prefix** of the request target.
   - If no route matches, it returns `404 Not Found`.

5. **Per‑route method allowance (for DEFAULT routes)**

   - For routes with `response_type == DEFAULT`, it checks whether the method
     is present in `route.default_response.accepted_methods`.
   - If not allowed, it returns `405 Method Not Allowed`.

6. **Dispatch by route type**

   ### STATIC routes

   - Use `route.static_response.status_code` and `route.static_response.text`.
   - Build a small HTML response (often used like a simple redirect or fixed page).
   - Do **not** touch the filesystem.

   ### DEFAULT routes

   1. **Map URI to filesystem**

      - Strip the route’s `uri` prefix from the request target.
      - Join the remaining relative path with `route.default_response.root`.

   2. **If the path is a directory**

      - If `index_file` is set:
        - Append it to the directory path and serve that file.
      - Else if `directory_listing_enabled` is true:
        - Generate a minimal autoindex HTML page listing directory entries.
      - Else:
        - Return `403 Forbidden`.

   3. **If the path is a file**

      - **GET**
        - Read the file into memory.
        - If successful: return `200 OK` with the file as the body and a
          `Content-Type` guessed from the file extension.
        - If reading fails: return `404 Not Found`.

      - **POST**
        - Overwrite or create the target file with the request body.
        - On success: return `201 Created` with a simple `"Created"` body.
        - On error: return `500 Internal Server Error`.

      - **DELETE**
        - Call `unlink` on the target path.
        - If the file does not exist: return `404 Not Found`.
        - On other errors: return `500 Internal Server Error`.
        - On success: return `200 OK` with `"Deleted"` as the body.

7. **Error pages**

   - For error codes such as `404`, `403`, `405`, `413`, `500`, the server:
     - Looks for a matching `t_error_page` in the configuration.
     - If a custom page is found and readable, it uses that file as the response body.
     - Otherwise, it generates a small fallback HTML error page.

---

In short, the Server class takes a parsed HTTP request, finds the right route, enforces method and body-size constraints, maps URIs to the filesystem for default routes, performs basic GET/POST/DELETE operations on files and directories, and returns a ServerResponse with the appropriate status code, content type, and body (using configured error pages when available).
