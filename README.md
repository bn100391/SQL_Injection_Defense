# SQL_Injection_Defense

## What is a SQL Injection Attack?: 🗣️  

An SQL Injection (SQLi) attack is a security vulnerability where an attacker tricks a website into running malicious SQL commands by injecting them into input fields
like login forms, search boxes, or URLs. It happens when a web application doesn't properly sanitize user input and directly uses that input in database queries. This
can let the attacker view and change the contents of databases, which can create all sorts of issues. 

---  

##  🛠️ What This Does: 
**Makes Use of Prepared Statments:** <br>
Prepared statements protect against SQL injection by keeping the SQL code separate from the user input.

Instead of building a query by directly inserting user input into the SQL string (which is risky), a prepared statement
uses placeholders for the data. The database treats the user input strictly as data, not as part of the SQL command. Thereby
removing the potential for the SQL logic to be changed. 
