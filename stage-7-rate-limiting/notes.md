# Stage 7: IP-Based Rate Limiting

## Objective

Prevent repeated attacks from the same IP address by tracking attack frequency and generating warnings when a predefined limit is exceeded.

## Features Implemented

* Reads requests from a file
* Extracts IP addresses from requests
* Detects SQL Injection attacks
* Detects XSS attacks
* Logs all request activity
* Tracks attack count per IP address
* Generates warnings when an IP exceeds the attack threshold
* Displays attack summary at program termination

## Concepts Learned

* Rate Limiting
* Request Tracking
* IP-Based Monitoring
* Security Event Logging
* Associative Containers (C++ map)

## Sample Attack Detection

SQL Injection:
' OR 1=1 --
UNION SELECT
DROP TABLE

XSS:

<script>alert(1)</script>

javascript:

## Sample Output

IP: 192.168.1.2
Request == ( login?user=admin' OR 1=1 -- )

Status: Blocked

Times attacked: 4

Blocked: 192.168.1.2 attacked more than 3 times (4 times)

## Outcome

The WAF can now identify repeated attackers and generate warnings for suspicious IP addresses. This provides basic protection against brute-force and repeated attack attempts.
