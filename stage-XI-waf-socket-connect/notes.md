# Day 11 - TCP Integration with Web Application Firewall (WAF)

## Project Objective

The objective of this stage was to integrate the previously developed TCP Client-Server application with the Web Application Firewall (WAF). Instead of reading requests from a text file, the WAF now receives live requests from a TCP client, inspects them against security rules, and returns an appropriate HTTP response.

---

# Features Implemented

- Integrated TCP Server with the existing WAF.
- Receive requests using `recv()`.
- Detect SQL Injection and XSS attacks using configurable rules.
- Read configuration values from `config.txt`.
- Maintain attack count for each IP using `std::map`.
- Log blocked requests into `log.txt`.
- Simulate backend processing using `backend.txt`.
- Send HTTP responses back to the client.
- Continuous server execution using `while(true)`.

---

# Project Architecture

```text
                Client
                   │
                   │ TCP Connection
                   ▼
        +-----------------------+
        |      WAF Server       |
        +-----------------------+
                   │
              recv(request)
                   │
                   ▼
          Rule Engine (rules.txt)
             /               \
            /                 \
     Malicious            Safe Request
         │                     │
         ▼                     ▼
    log.txt             backend.txt
         │                     │
         └────────┬────────────┘
                  ▼
          HTTP Response Sent
                  │
                  ▼
                Client
```

---

# Workflow

```text
Client

↓

Connect to WAF Server

↓

Send HTTP Request

↓

Server receives request

↓

Check request against rules.txt

↓

Attack Found?
      │
 ┌────┴────┐
 │         │
Yes        No
 │          │
 ▼          ▼
Log      Forward to Backend
 │          │
 ▼          ▼
403      200 OK
 │          │
 └────┬─────┘
      ▼
 Client receives response
```

---

# Files Used

| File | Description |
|------|-------------|
| `client.cpp` | Sends requests to the WAF server |
| `server.cpp` | TCP-based Web Application Firewall |
| `rules.txt` | Stores SQL Injection and XSS detection rules |
| `config.txt` | Stores configurable maximum attack limit |
| `log.txt` | Stores blocked requests and attack logs |
| `backend.txt` | Simulates the backend server by storing safe requests |

---

# Concepts Learned

- TCP Socket Programming
- Client-Server Communication
- Request Processing
- Rule-Based Security
- Configuration Files
- Logging
- Attack Counting
- HTTP Response Generation
- Modular Programming
- Code Reusability

---

# Sample Outputs

## Safe Request

**Client Input**

```
GET /home
```

**Server Response**

```
HTTP/1.1 200 OK
```

---

## SQL Injection Attack

**Client Input**

```
GET /login?id=1 OR 1=1
```

**Server Response**

```
HTTP/1.1 403 Forbidden
```

---

## XSS Attack

**Client Input**

```
<script>alert(1)</script>
```

**Server Response**

```
HTTP/1.1 403 Forbidden
```

---

# Learning Outcome

This stage transformed the project from a file-based Web Application Firewall into a network-enabled WAF. The server now accepts live client connections, inspects incoming requests in real time, blocks malicious traffic, logs attacks, and forwards safe requests to a simulated backend.

This implementation demonstrates the integration of networking, application security, and modular software design, providing a strong foundation for building a Reverse Proxy Web Application Firewall in the next stage.

---

# Technologies Used

- C++
- Linux/macOS Socket Programming
- TCP/IP
- File Handling
- STL (`map`, `string`, `stringstream`)
- HTTP Basics

---

# Next Goal

Build a real **Backend Server** and convert the project into a complete **Reverse Proxy Web Application Firewall**, where safe requests are forwarded to an actual backend server instead of a text file.
