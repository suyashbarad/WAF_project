# Day 15 – Advanced WAF Security Enhancements

## Overview
Day 15 combines three development phases into one milestone. During this stage, the Web Application Firewall became significantly more practical by improving attack detection, logging, request validation, and HTTP handling.

The WAF now performs request inspection before forwarding traffic to the backend server while maintaining detailed security logs.

---

## Features Added

### 1. Regex-Based Attack Detection
- Replaced simple substring matching with Regular Expressions.
- Case-insensitive detection.
- Detects obfuscated attacks.

Examples:
- OR      1 = 1
- UNION      SELECT
- <ScRiPt>
- select * from
- drop table

---

### 2. Improved SQL Injection Detection

Protected against:

- OR 1=1
- UNION SELECT
- SELECT * FROM
- DROP TABLE

using regex patterns.

---

### 3. Improved XSS Detection

Protected against:

- <script>
- <ScRiPt>
- <script     >
- mixed-case script tags

---

### 4. Full Request Scanning

Instead of checking only a single word, the WAF now scans the complete request path, making detection significantly more accurate.

---

### 5. Request Size Limiting

Large payloads are automatically blocked.

Response:
HTTP 413 Payload Too Large

Prevents oversized request attacks.

---

### 6. Timestamp Logging

Every request now records:

- Timestamp
- IP Address
- HTTP Method
- Requested Path
- Status
- Action Taken

---

### 7. Better Log Formatting

Logs are now easier to read using formatted separators.

Example:

========================================
Time
IP
Method
Request
Status
Action
========================================

---

### 8. HTTP Parsing Improvements

Request parsing was simplified to correctly process paths containing spaces.

---

### 9. Child Process Cleanup

Improved process handling after request completion to avoid unnecessary zombie processes.

---

### 10. Existing Features Retained

- SQL Injection Detection
- XSS Detection
- Invalid HTTP Method Detection
- IP Blocking
- Configurable Attack Threshold
- Backend Request Forwarding
- Client-Server Communication
- Backend Response Relay

---

## Files

server.cpp

client.cpp

backend.cpp

rules.txt

config.txt

log.txt

backend.txt

---

## Sample Attacks Tested

✔ GET <script>alert(1)</script>

✔ GET <ScRiPt>alert(1)</ScRiPt>

✔ GET UNION SELECT

✔ GET UNION      SELECT

✔ GET OR 1 = 1

✔ GET OR      1=1

✔ GET DROP TABLE users

✔ Invalid HTTP Method

✔ Oversized Request

---

## Result

All malicious requests were blocked before reaching the backend.

Legitimate requests were forwarded successfully.

Detailed logs were generated for every request.

---

## Technologies Used

- C++
- Socket Programming
- TCP/IP
- Linux/macOS System Calls
- Regex
- File Handling
- Process Management
