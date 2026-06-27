# Stage 8: Configurable WAF (Rule Engine)

## Objective

Transform the Web Application Firewall into a configurable security engine by removing hardcoded values and loading both attack rules and configuration from external files.

## Features

* Detects SQL Injection attacks
* Detects XSS attacks
* Reads HTTP requests from `request.txt`
* Logs every processed request
* Tracks attacks for each IP address
* Implements IP-based rate limiting
* Reads maximum attack limit from `config.txt`
* Loads security rules dynamically from `rules.txt`
* Generates attack summary

## Configuration File

config.txt

MAX_ATTACKS=3

Changing this value updates the WAF behaviour without modifying or recompiling the source code.

## Rule Engine

# ` rules.txt ` <br>

-` OR 1=1 ` <br>
-` '-- ` <br>
-` SELECT * FROM ` <br>
-` UNION SELECT ` <br>
-` DROP TABLE ` <br>
-` <script> ` <br>
-` javascript: ` <br>

Adding a new detection rule only requires adding another line to `rules.txt`.

No source code changes are needed.

## Concepts Learned

- File Handling
- stringstream
- stoi()
- C++ map
- Dynamic Rule Loading
- Configuration Files
- Rate Limiting
- Rule Engine
- Security Logging

## Sample Output

IP: 192.168.1.2

Request == ( DROP TABLE users )

Status: Blocked

Times attacked: 4

Blocked: 192.168.1.2 attacked more than 3 times (4 times)

--------------Attack Summary--------------

192.168.1.2 == 4 times -- WARNING exceeded 3 attacks

## Outcome

The WAF has evolved from a simple hardcoded scanner into a configurable security engine. Attack signatures and security policies are now maintained through external files, making the application easier to extend and maintain.
