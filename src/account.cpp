//
//  account.cpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#include "account.hpp"
Account::Account(int ID, std::string type, double balance)
    : ID(ID), type(type), balance(balance) {}

void Account::add_to_balance(double amount) { balance += amount; }

void Account::take_from_balance(double amount) { balance -= amount; };

int Account::get_id() const { return ID; }

std::string Account::get_type() const { return type; }

double Account::get_balance() const { return balance; }
