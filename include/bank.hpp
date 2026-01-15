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
#include "transaction.hpp"

class Bank {
 private:
	SQLite::Database db;
	std::vector<Customer> customers;
	std::vector<Transaction> transactions_hist;

 public:
	Bank(const std::filesystem::path &path);

	bool init();

	std::expected<void, std::string> load_history();
	std::vector<Transaction> get_history();

	void save_customer(const Customer &customer);
	void add_customer(const Customer &customer);

	void add_account_for_customer(Customer &cust, Account &acc);

	void load_customers();
	Customer *get_customer(int ID);

	std::vector<Customer> get_customers() const;

	// Updates in DB
	std::expected<void, std::string> update_account //
	    (Customer &customer, Account &account);

	std::expected<void, std::string> record_transaction //
	    (Transaction &trans);

	// Transaction methods
	std::expected<void, std::string> deposit //
	    (Customer &customer, Account &account, double amount);

	std::expected<void, std::string> withdraw //
	    (Customer &customer, Account &account, double amount);

	std::expected<void, std::string> transfer        //
	    (Customer &from_customer, Account &from_acc, //
	     Customer &to_customer, Account &to_acc, double amount);
};
