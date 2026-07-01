# 📅 Day 12–13: TCP Networking & Reverse Proxy Integration

## 🚀 Overview

In this update, the Web Application Firewall (WAF) was transformed from a file-based request analyzer into a real TCP network application.

A dedicated backend server was implemented, and the WAF now acts as a **Reverse Proxy**, inspecting all incoming requests before deciding whether to block them or forward them to the backend server.

---

## ✅ Features Implemented

### 🔹 TCP Client
- Built a client application using C++ socket programming.
- Establishes a TCP connection with the WAF server.
- Sends HTTP-like requests entered by the user.
- Displays responses received from the server.

---

### 🔹 WAF Server
- Accepts incoming client connections.
- Reads security rules from `rules.txt`.
- Reads attack threshold from `config.txt`.
- Detects SQL Injection and XSS attacks.
- Maintains per-IP attack counts.
- Logs every request and attack.
- Blocks malicious requests with **HTTP 403 Forbidden**.
- Forwards safe requests to the backend server.

---

### 🔹 Backend Server
- Implemented as an independent TCP server.
- Listens on a separate port (9090).
- Receives only safe requests forwarded by the WAF.
- Processes the request.
- Sends an HTTP 200 OK response back to the WAF.

---

## 🔄 Reverse Proxy Workflow

```text
            Client
               │
               ▼
      WAF Server (Port 8080)
               │
      ┌────────┴────────┐
      │                 │
 Malicious          Safe Request
      │                 │
403 Forbidden           ▼
                  Backend Server
                    (Port 9090)
                        │
                        ▼
                 HTTP 200 Response
                        │
                        ▼
                   Client
```

---

## 🛡️ Security Features

- SQL Injection Detection
- Cross-Site Scripting (XSS) Detection
- Configurable attack threshold
- External rule management
- Attack logging
- IP attack counting
- Reverse proxy request filtering

---

## 📂 Files Added

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

## 🧠 Concepts Learned

- TCP Socket Programming
- Client-Server Architecture
- Socket API (`socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, `recv()`)
- Reverse Proxy Architecture
- Request Forwarding
- HTTP Status Responses
- Rule-Based Packet Inspection
- File Handling
- Configuration Files
- Logging
- IP Tracking using STL Map

---

## ✅ Sample Outputs

### Safe Request

```
Input:
GET /home

Client
↓
WAF
↓
Backend
↓
HTTP/1.1 200 OK

Welcome to Backend Server!
```

---

### Malicious Request

```
Input:
<script>alert(1)</script>

Client
↓
WAF
↓
Rule Matched
↓
HTTP/1.1 403 Forbidden
```

---

## 📌 Summary

This milestone converts the project from a standalone request analyzer into a functional **Reverse Proxy Web Application Firewall (WAF)**. The WAF now filters incoming traffic in real time, blocks malicious requests, and securely forwards legitimate requests to a backend server, closely resembling the workflow of production reverse proxies such as Nginx with ModSecurity.
