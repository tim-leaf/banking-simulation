//
//  account.hpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <iostream>

using std::string;

class Account {
 private:
	int ID;
	string type;

	double balance;

 public:
	Account(int ID, string type, double balance);

	void add_to_balance(double amount);
	void take_from_balance(double amount);

	int get_id() const;
	string get_type() const;

	double get_balance() const;
};
