# Day 9 - TCP Socket Programming (Client-Server Communication)

## Project Objective

The goal of this module was to understand how two independent C++ programs communicate over a network using TCP sockets.

This knowledge will later be used to convert my file-based Web Application Firewall (WAF) into a real network-based WAF.

---

# Client-Server Architecture

```
           Client
              │
        connect()
              │
              ▼
           Server
     socket → bind → listen → accept
```

- Server waits for incoming connections.
- Client initiates the connection.
- Once connected, both can exchange data.

---

# Socket Lifecycle

```
socket()

↓

bind()

↓

listen()

↓

accept()

↓

recv()

↓

send()

↓

close()
```

---

# Functions Learned

## 1. socket()

Creates a communication endpoint.

### Syntax

```cpp
int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
```

### Real-Life Analogy

Buying a phone.

Before talking to anyone, you first need a phone.

---

## 2. bind()

Assigns an IP address and port number to the server socket.

### Syntax

```cpp
bind(serverSocket,
     (sockaddr*)&serverAddress,
     sizeof(serverAddress));
```

### Real-Life Analogy

Getting a phone number for your phone.

---

## 3. listen()

Starts listening for incoming client connections.

### Syntax

```cpp
listen(serverSocket, 5);
```

### Real-Life Analogy

Turning your phone ON and waiting for calls.

---

## 4. accept()

Accepts an incoming client connection.

### Syntax

```cpp
clientSocket = accept(serverSocket, NULL, NULL);
```

### Real-Life Analogy

Answering the phone when someone calls.

---

## Why Two Sockets?

```
serverSocket

↓

Reception Desk

clientSocket

↓

Current Customer
```

- serverSocket keeps waiting for new clients.
- clientSocket communicates with one connected client.

---

## 5. connect()

Used by the client to connect to the server.

### Syntax

```cpp
connect(clientSocket,
        (sockaddr*)&serverAddress,
        sizeof(serverAddress));
```

### Real-Life Analogy

Dialing someone's phone number.

---

## 6. recv()

Receives data sent by the other side.

### Syntax

```cpp
recv(clientSocket,
     buffer,
     sizeof(buffer),
     0);
```

### Real-Life Analogy

Reading a letter from your mailbox.

---

## 7. send()

Sends data to the other side.

### Syntax

```cpp
send(clientSocket,
     response.c_str(),
     response.length(),
     0);
```

### Real-Life Analogy

Writing and posting a reply.

---

## 8. close()

Closes the socket connection.

### Syntax

```cpp
close(clientSocket);
close(serverSocket);
```

### Real-Life Analogy

Hanging up the phone.

---

# Important Concepts

## IP Address

An IP address uniquely identifies a device on a network.

Example

```
127.0.0.1
```

This is called **localhost**, which always refers to your own computer.

---

## Port Number

A port identifies a specific application running on a computer.

Example

```
8080
```

Multiple applications can run on one computer because each uses a different port.

---

## AF_INET

Indicates IPv4 addressing.

---

## SOCK_STREAM

Specifies TCP communication.

TCP provides:

- Reliable communication
- Ordered delivery
- Error checking

---

## Buffer

```
char buffer[1024];
```

A buffer is temporary storage where received data is kept.

Real-Life Analogy:

A mailbox that temporarily stores letters until someone reads them.

---

## inet_pton()

Converts a readable IP address into a format understood by the operating system.

Example

```cpp
inet_pton(AF_INET,
          "127.0.0.1",
          &serverAddress.sin_addr);
```

---

## c_str()

Converts a C++ string into a C-style string.

Example

```cpp
string response = "HTTP/1.1 200 OK";

response.c_str();
```

This is required because socket functions work with character arrays.

---

# Complete Communication Flow

```
Client

↓

socket()

↓

connect()

↓

send("GET /home")

↓

-----------------------------

Server

↓

socket()

↓

bind()

↓

listen()

↓

accept()

↓

recv()

↓

Process Request

↓

send("HTTP/1.1 200 OK")

↓

-----------------------------

Client

↓

recv()

↓

Display Response
```

---


# Outcome

Successfully built a complete TCP Client-Server application in C++.

The server can:

- Accept client connections
- Receive requests
- Send responses

The client can:

- Connect to the server
- Send requests
- Receive server responses

This networking module forms the foundation for the next stage of the project, where the Web Application Firewall (WAF) will inspect real network requests instead of reading them from a text file.
