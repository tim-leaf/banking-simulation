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

class Customer {
 private:
	int ID;
	std::string name;

	std::vector<Account> accounts{};

 public:
	Customer(int ID, std::string name);

	int get_id() const;
	std::string get_name() const;

	Account *get_account(int ID);
	std::vector<Account> get_accounts() const;

	void add_account(const Account &account);
};
