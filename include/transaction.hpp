//
//  transaction.hpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 15/01/2026.
//

#pragma once
#include "account.hpp"
#include "customer.hpp"
#include <iostream>
#include <string>

class Transaction {
 public:
	Customer *from;
	Customer *to;

	int id;

	double amount;
	std::string type;

	Transaction(Customer *from, Customer *to, double amount,
	            const std::string &type, int id = -1);

	void set_id(int n_id) { id = n_id; }
};
