# Day 14 - HTTP Parsing, Validation & IP Blacklisting

## Features Added

### 1. HTTP Request Parsing

Implemented parsing of incoming HTTP requests into:

- Method
- Path
- HTTP Version

Example:

GET /home HTTP/1.1

Parsed Output:

Method : GET
Path : /home
Version : HTTP/1.1

---

### 2. HTTP Method Validation

Added validation for supported methods:

- GET
- POST
- PUT
- DELETE

Invalid methods return:

HTTP/1.1 400 Bad Request

Example:

HELLO /home HTTP/1.1

Result:

400 Bad Request

---

### 3. URL-Based Attack Detection

Modified WAF scanning logic to inspect only the URL path instead of the complete request.

Example:

GET /login?id=1 OR 1=1 HTTP/1.1

The WAF checks:

/login?id=1 OR 1=1

against rules stored in rules.txt.

---

### 4. Attack Counter

Each malicious request increments the attack count for the source IP.

Example:

127.0.0.1 → Attack Count = 3

---

### 5. IP Blacklisting

If attack count exceeds the configured threshold:

MAX_ATTACKS=3

the IP is automatically blacklisted.

Blacklisted IPs receive:

HTTP/1.1 403 Forbidden

IP Blacklisted

---

### 6. Improved Logging

Logs now contain:

- IP Address
- Request Path
- Attack Count
- Block Status
- Blacklist Status

---

## Test Cases

### Safe Request

GET /home HTTP/1.1

Response:

HTTP/1.1 200 OK

---

### SQL Injection

GET /login?id=1 OR 1=1 HTTP/1.1

Response:

HTTP/1.1 403 Forbidden

Attack Detected

---

### XSS Attack

GET /<script>alert(1)</script> HTTP/1.1

Response:

HTTP/1.1 403 Forbidden

Attack Detected

---

### Invalid Method

HELLO /home HTTP/1.1

Response:

HTTP/1.1 400 Bad Request

---

### Blacklisted IP

After exceeding MAX_ATTACKS:

HTTP/1.1 403 Forbidden

IP Blacklisted

---

## Concepts Learned

- HTTP Request Structure
- Request Parsing
- URL Inspection
- Method Validation
- Attack Tracking
- IP Blacklisting
- TCP Socket Programming
- Reverse Proxy Security
