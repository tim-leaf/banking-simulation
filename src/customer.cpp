//
//  customer.cpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#include "customer.hpp"
Customer::Customer(int ID, string name) : ID(ID), name(std::move(name)) {}

int Customer::get_id() const { return ID; }

string Customer::get_name() const { return name; }

vector<Account> Customer::get_accounts() const { return accounts; }

Account *Customer::get_account(int ID) {
	for (auto &acc : accounts) {
		if (acc.get_id() == ID) {
			return &acc;
		}
	}

	return nullptr;
}

void Customer::add_account(const Account &account) {
	accounts.emplace_back(account);
}
