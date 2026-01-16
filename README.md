# SQL Banking Simulation

A console-based banking simulation built in C++ using the **SQLiteCpp** library for database persistence.
This project demonstrates advanced object-oriented design, database integration, and real-world software engineering practices.


---
## Description

The SQL Banking Simulation allows users to manage **customers** and **accounts**, perform **transactions**, and store all data in a persistent SQLite database.
The system is designed to be modular, maintainable, and easily extendable.


---
## What this project demonstrates

- Clean project structure and documentation
- Error handling with std::expected
- Object-Oriented Design in C++
- SQL database integration
- Data consistency


---
## Project Structure

```
BankingSimulation/
├── README.md
│
├── src/
│   ├── main.cpp              # Entry point + CLI
│   ├── account.cpp
│   ├── customer.cpp
│   └── bank.cpp
│
└── include/
    ├── account.hpp           # Account class
    ├── customer.hpp          # Customer class
    └── bank.hpp              # Bank class + DB interactions
```
