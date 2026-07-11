# 🛡️ Web Application Firewall (WAF)

> A lightweight Web Application Firewall built in **C++** using **Socket Programming** to detect, filter, and block common web attacks before forwarding legitimate requests to a backend server.

---

## 📌 Project Overview

> This project implements a **reverse proxy Web Application Firewall (WAF)** that sits between a client and a backend server. Every incoming request is inspected for malicious content before being forwarded to the backend.

The WAF protects against common web attacks such as:

- SQL Injection (SQLi)
- Cross-Site Scripting (XSS)
- Invalid HTTP Requests
- Missing HTTP Headers
- Oversized Payload Attacks
- Unauthorized URL Access
- Excessive Request Flooding (Rate Limiting)

Only legitimate requests are forwarded to the backend server.

---

# 🎯 Objectives

- Understand Socket Programming
- Learn Client-Server Communication
- Build a Reverse Proxy
- Detect Web Attacks
- Filter Malicious Requests
- Log Security Events
- Measure WAF Performance
- Understand Basic Web Security Concepts

---

# 🏗️ Project Architecture

```text
                +------------------+
                |      Client      |
                +------------------+
                         |
                         |
                    HTTP Request
                         |
                         ▼
            +-----------------------+
            |   Web Application     |
            |      Firewall         |
            +-----------------------+
          /       |        |       \
         /        |        |        \
 Validation   Detection  Logging  Filtering
         \        |        |       /
          \       |        |      /
           \      |        |     /
                  ▼
          Safe Request Only
                  |
                  ▼
         +-------------------+
         |   Backend Server  |
         +-------------------+
```

---

# 📂 Project Structure

```text
WAF/
│
├── client.cpp
├── server.cpp
├── backend.cpp
│
├── rules.txt
├── whitelist.txt
├── blacklist.txt
├── config.txt
│
├── log.txt
├── backend.txt
│
└── README.md
```

---

# ⚙️ Technologies Used

- C++
- Linux Socket Programming
- TCP/IP Networking
- POSIX System Calls
- Regular Expressions (Regex)
- File Handling
- Process Management (`fork()`)
- STL Containers
- Time & Performance APIs

---

# ✨ Features

## 🌐 Networking

- TCP Socket Programming
- Client-Server Communication
- Backend Server
- Reverse Proxy
- Multiple Client Handling using `fork()`

---

## 🔒 Security Features

### ✅ SQL Injection Detection

Detects attacks such as:

```text
OR 1=1
```

```text
UNION SELECT
```

```text
DROP TABLE
```

---

### ✅ Cross Site Scripting (XSS)

Detects payloads like:

```html
<script>alert(1)</script>
```

---

### ✅ Regex Rule Matching

Uses configurable regex rules stored in:

```text
rules.txt
```

Example:

```text
or\s+1\s*=\s*1
union\s+select
drop\s+table
<script\s*>
```

---

### ✅ Custom Rule Support

Rules can be added or modified without changing the source code.

---

### ✅ HTTP Method Validation

Allows only:

```text
GET
POST
PUT
DELETE
```

Invalid methods are rejected.

---

### ✅ HTTP Header Validation

Required headers:

- Host
- User-Agent
- Content-Type

Missing headers are blocked.

---

### ✅ Request Size Validation

Oversized payloads receive:

```text
HTTP 413 Payload Too Large
```

---

### ✅ URL Whitelisting

Allowed URLs are stored in:

```text
whitelist.txt
```

Only these requests reach the backend.

---

### ✅ URL Blacklisting

Blocked URLs are stored in:

```text
blacklist.txt
```

These are rejected immediately.

---

### ✅ Rate Limiting

Limits requests from the same IP within a configurable time window.

Example:

```text
3 requests / minute
```

Returns:

```text
HTTP 429 Too Many Requests
```

---

### ✅ IP Blocking

Repeated malicious requests lead to automatic IP blocking.

---

# 📄 Logging System

Every request is logged with:

- Timestamp
- Client IP
- HTTP Method
- Requested URL
- Request Size
- Status
- Action Taken
- Processing Time

Example:

```text
========================================
Time : 2026-07-04 00:54:05
IP : 127.0.0.1
Method : GET
Request : hello
Status : Safe
Processing Time : 2 ms
========================================
```

---

# ⚡ Performance Monitoring

The WAF measures processing latency for every request.

Example:

```text
Processing Time : 2 ms
```

This includes:

- Parsing
- Header Validation
- Regex Matching
- Logging
- Backend Forwarding

---

# 📋 Configuration Files

### config.txt

Stores configurable parameters.

Example:

```text
MAX_ATTACKS=3
```

---

### rules.txt

Stores SQL Injection and XSS detection patterns.

---

### whitelist.txt

Contains allowed URLs.

---

### blacklist.txt

Contains blocked URLs.

---

# 📚 Concepts Learned During This Project

## Socket Programming

- TCP Communication
- Client-Server Architecture
- Socket Creation
- Binding
- Listening
- Accepting Connections
- Sending & Receiving Data

---

## Operating System Concepts

- Process Creation using `fork()`
- Parent & Child Processes
- Process Cleanup (`wait()`)
- File Descriptors
- System Calls

---

## Networking Concepts

- TCP/IP
- Ports
- IP Addressing
- HTTP Request Flow
- Reverse Proxy
- Backend Communication

---

## Security Concepts

- Web Application Firewall (WAF)
- SQL Injection
- Cross-Site Scripting (XSS)
- HTTP Request Validation
- HTTP Header Validation
- Request Filtering
- Payload Size Limiting
- URL Whitelisting
- URL Blacklisting
- Rate Limiting
- IP Blocking
- Logging Security Events

---

## C++ Concepts

- File Handling
- Regular Expressions
- STL Map
- STL Vector
- String Streams
- Time Functions
- Modular Programming
- Error Handling

---

# 🧪 Test Cases

| Test Case | Expected Result |
|------------|-----------------|
| Safe Request | Forward to Backend |
| SQL Injection | Blocked (403) |
| XSS Attack | Blocked (403) |
| Invalid Method | Bad Request (400) |
| Missing Headers | Blocked (400) |
| Large Payload | Blocked (413) |
| Blacklisted URL | Blocked |
| Whitelisted URL | Allowed |
| Excessive Requests | Rate Limited (429) |

---

# 🚀 How to Run

Compile the files:

```bash
g++ backend.cpp -o backend
g++ server.cpp -o server
g++ client.cpp -o client
```

Run in separate terminals:

```bash
./backend
```

```bash
./server
```

```bash
./client
```

---

# 📈 Learning Outcomes

By completing this project, I gained hands-on experience with:

- Building a reverse proxy
- Implementing a basic Web Application Firewall
- Socket programming in C++
- Client-server architecture
- HTTP request parsing
- Regular expressions
- File-based configuration
- Security rule implementation
- Logging and monitoring
- Performance measurement
- Secure request filtering

---

# 🔮 Future Improvements

- HTTPS/TLS Support
- Multi-threaded Client Handling
- Shared-memory or Redis-based Rate Limiting
- Rule Management Dashboard
- Admin Panel
- Docker Deployment
- Reverse Proxy Deployment (Nginx)
- Cloud Deployment (AWS/Azure)
- Real-time Monitoring Dashboard

---

##  #Author
**Suyash Sachin Barad**  
B.Tech Computer Science & Engineering  
MIT World Peace University (MIT-WPU)

📍 Pune, Maharashtra, India  
🔗 [GitHub](https://github.com/suyashbarad) | [LinkedIn](https://www.linkedin.com/in/suyash-sachin-barad-796b6534b) | [HackerRank](https://www.hackerrank.com/profile/baradsuyash4)

---


# ⭐ Project Status

**Completed**

This project successfully demonstrates the implementation of a basic **Web Application Firewall (WAF)** capable of filtering malicious HTTP requests, protecting backend services, logging security events, and forwarding only validated traffic. It also serves as a practical learning project covering networking, operating systems, web security, and modern C++ programming concepts.
