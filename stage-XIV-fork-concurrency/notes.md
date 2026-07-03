# Day 14 - Concurrent Web Application Firewall (WAF)

## Objective
Upgrade the WAF from handling a single client to handling multiple clients concurrently using the Unix `fork()` system call.

---

## Features Implemented

- Concurrent client handling using `fork()`
- Parent process continues listening for incoming connections
- Child process handles client requests independently
- Automatic child process cleanup using `waitpid()`
- SQL Injection detection using configurable rules
- XSS detection using configurable rules
- HTTP request parsing
- HTTP method validation
- IP attack counting
- Automatic IP blacklisting after configurable attack limit
- Request logging
- Safe request forwarding to backend server
- Backend response forwarding to client
- Configurable maximum attack count using `config.txt`

---

## Project Architecture

```
                Client
                  |
                  |
          TCP Port 8080
                  |
          -----------------
          |      WAF      |
          -----------------
          |               |
     Attack?          Safe Request
          |               |
     Block Request        |
          |               |
          |         TCP Port 9090
          |               |
          |        Backend Server
          |               |
          -----------------
                  |
               Response
                  |
               Client
```

---

## Technologies Used

- C++
- Linux/macOS Socket Programming
- TCP/IP
- Process Management (`fork()`)
- `waitpid()`
- File Handling
- HTTP Request Parsing
- STL Map

---

## Detection Rules

Current attacks detected:

- SQL Injection
- XSS
- UNION SELECT
- DROP TABLE
- OR 1=1
- '--

Rules are loaded dynamically from `rules.txt`.

---

## Configuration

Maximum attack attempts are loaded from:

```
config.txt
```

Example:

```
MAX_ATTACKS=3
```

---

## Files

```
client.cpp
server.cpp
backend.cpp
rules.txt
config.txt
log.txt
backend.txt
```

---

## Compile

```bash
g++ server.cpp -o server
g++ backend.cpp -o backend
g++ client.cpp -o client
```

---

## Run

Terminal 1

```bash
./backend
```

Terminal 2

```bash
./server
```

Terminal 3

```bash
./client
```

---

## Sample Attack

```
Method:
get

Path:
<script>alert(1)</script>
```

Response

```
HTTP/1.1 403 Forbidden
Attack try
```

---

## Learning Outcomes

- Socket Programming
- HTTP Request Parsing
- Multi-process Servers
- Parent and Child Process Management
- TCP Communication
- Web Application Firewall Basics
- Backend Request Forwarding
- Rule-based Attack Detection
- Process Synchronization using `waitpid()`

---

## Day 14 Status

Completed Successfully
