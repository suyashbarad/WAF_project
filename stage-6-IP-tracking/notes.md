# Stage 7: IP Tracking and Request Attribution
## Objective
Identify which IP address generated each request and determine whether the request is safe or malicious.
Features Implemented
* Reads requests from a file
* Extracts IP addresses using stringstream
* Detects SQL Injection attacks
* Detects XSS attacks
* Logs all requests and results into a log file
## Concepts Learned
* Request parsing
* IP attribution
* Logging
* Basic security analysis
## Sample Output
IP: 192.168.1.2 Request: login?user=admin' OR 1=1 -- Status: Blocked
