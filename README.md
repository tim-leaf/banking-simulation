# SQL Banking Simulation

A console-based banking simulation built in C++ using the **SQLiteCpp** library for database persistence.
This project demonstrates advanced object-oriented design, database integration, and real-world software engineering practices.


---
## Overview

The SQL Banking Simulation allows users to manage **customers** and **accounts**, perform **transactions**, and store all data in a persistent SQLite database.
The system is designed to be modular, maintainable, and easily extendable.

Key features include:
```
	-[x] Customer creation and management
	-[x] Multiple account types (e.g. checking, savings)
	-[x] Deposits, withdrawals, and transfers
	-[_] Transaction logging
	-[x] Persistent storage via SQLite
	-[x] Input validation and error handling
```


---
## Project Structure

```
BankingSimulation/
├── README.md                 # Project description & documentation
│
├── src/                      # Source files
│   ├── main.cpp              # Entry point + CLI
│   ├── account.cpp
│   ├── customer.cpp
│   └── bank.cpp
│
├── include/                  # Header files
│   ├── account.hpp           # Account class
│   ├── customer.hpp          # Customer class
│   └── bank.hpp              # Bank class + DB interactions
```
