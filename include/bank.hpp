//
//  bank.hpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

#include <cstdint>
#include <expected>
#include <filesystem>
#include <iostream>
#include <optional>
#include <vector>

#include "customer.hpp"

namespace fs = std::filesystem;
using std::vector;

class Bank {
 private:
	SQLite::Database db;
	vector<Customer> customers;

 public:
	Bank(const fs::path &path);

	bool init();

	void save_customer(const Customer &customer);
	void add_customer(const Customer &customer);

	void add_account_for_customer(Customer &cust, Account &acc);

	void load_customers();
	Customer *get_customer(int ID);

	vector<Customer> get_customers() const;

	// Transaction methods
	std::expected<bool, string> deposit(Customer &customer, Account &account, double amount);

	std::expected<bool, string> withdraw(Customer &customer, int account_id,
	                                     double amount);

	bool transfer(int from_customer_id, int from_acc_id, //
	              int to_customer_id, int to_acc_id, double amount);
};
