# WAF Logic (C++)

## What I built
A basic Web Application Firewall logic that detects malicious requests.

## Attacks detected
- SQL Injection
- XSS

## Example attacks

SQL Injection:
' OR 1=1 --

XSS:
<script>alert(1)</script>

## Working
The program checks if request contains dangerous patterns and blocks it.
