//
//  account.hpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>

class Account {
 private:
	int ID;
	std::string type;

	double balance;

 public:
	Account(int ID, std::string type, double balance);

	void add_to_balance(double amount);
	void take_from_balance(double amount);

	int get_id() const;
	std::string get_type() const;

	double get_balance() const;
};
