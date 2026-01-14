//
//  customer.hpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <cstdint>
#include <string>
#include <vector>

#include "account.hpp"

using std::string, std::vector;

class Customer {
 private:
	int ID;
	string name;

	vector<Account> accounts{};

 public:
	Customer(int ID, string name);

	int get_id() const;
	string get_name() const;

	Account *get_account(int ID);
	vector<Account> get_accounts() const;

	void add_account(const Account &account);
};
