# Stage 4: File-Based Request Processing

## What I did

In this stage, I improved my WAF logic to read multiple requests from a file instead of manual input.

## Why this is important

In real-world systems, requests come continuously from users.
Instead of checking one request manually, the system must process multiple requests automatically.

## Implementation

* Created a file `requests.txt` containing sample requests
* Modified C++ program to read each request line by line
* Checked each request for malicious patterns (SQL Injection, XSS)

## Outcome

* The WAF can now process multiple requests automatically
* Each request is classified as SAFE or BLOCKED

## Next Goal

Add logging system to store requests and results
