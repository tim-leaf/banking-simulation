//
//  bank.cpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#include "bank.hpp"

Bank::Bank(const fs::path &path)
    : db(path.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {}

bool Bank::init() {
	try {

		// Create customers table if it doesn't exist
		db.exec("CREATE TABLE IF NOT EXISTS customers ("
		        "id INTEGER PRIMARY KEY, "
		        "name TEXT NOT NULL"
		        ");");

		// Create accounts table if it doesn't exist
		db.exec("CREATE TABLE IF NOT EXISTS accounts("
		        "	id INTEGER NOT NULL,"
		        "	customer_id INTEGER NOT NULL,"
		        "	type TEXT NOT NULL,"
		        "	balance REAL NOT NULL,"
		        "	PRIMARY KEY (customer_id, id),"
		        "	FOREIGN KEY(customer_id) REFERENCES customers(id)"
		        ");");

		// Create transaction table for logging
		db.exec("CREATE TABLE IF NOT EXISTS transactions("
		        "	id INTEGER PRIMARY KEY,"
		        "	account_from INTEGER,"
		        "	account_to INTEGER,"
		        "	amount REAL,"
		        "	timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
		        ");");

	} catch (std::exception &e) {
		std::cerr << "Database initialization error: " << e.what() << "\n";
		return false;
	}

	return true;
}

#pragma mark - Add Customer
void Bank::save_customer(const Customer &customer) {
	try {

		SQLite::Statement query(db, "INSERT OR REPLACE INTO customers "
		                            "(id, name) VALUES (?, ?);");

		query.bind(1, int(customer.get_id()));
		query.bind(2, customer.get_name());

		query.exec();

		// Save all accounts of this customer
		for (const auto &acc : customer.get_accounts()) {
			SQLite::Statement acc_query(
			    db, "INSERT OR REPLACE INTO accounts "
			        "(id, customer_id, type, balance) VALUES (?, ?, ?, ?);");

			acc_query.bind(1, int(acc.get_id()));
			acc_query.bind(2, int(customer.get_id()));
			acc_query.bind(3, acc.get_type());
			acc_query.bind(4, acc.get_balance());

			acc_query.exec();
		}

	} catch (std::exception &e) {
		std::cerr << e.what() << '\n';
	}
}

void Bank::add_customer(const Customer &customer) {
	customers.push_back(customer);

	save_customer(customer);

	load_customers();
}

void Bank::add_account_for_customer(Customer &cust, Account &acc) {
	cust.add_account(acc);

	// Save account to SQLite
	try {

		SQLite::Statement query(
		    db, "INSERT OR REPLACE INTO accounts(id, customer_id, type,  "
		        "balance) VALUES (?, ?, ?, ?);");
		query.bind(1, acc.get_id());
		query.bind(2, cust.get_id());
		query.bind(3, acc.get_type());
		query.bind(4, acc.get_balance());
		query.exec();

	} catch (const std::exception &e) {
		std::cerr << "Failed to save account to DB: " << e.what() << '\n';
	}
}

#pragma mark - Get customer
void Bank::load_customers() {
	customers.clear();

	try {

		SQLite::Statement query(db, "SELECT id, name FROM customers;");

		// Load all customers
		while (query.executeStep()) {
			int id = query.getColumn(0).getInt();
			string name = query.getColumn(1).getText();
			customers.emplace_back(Customer(id, name));
		}

		// Load all accounts
		SQLite::Statement acc_query(db, "SELECT id, customer_id, "
		                                "type, balance FROM accounts");
		while (acc_query.executeStep()) {
			int acc_id = int(acc_query.getColumn(0).getInt());
			int cust_id = int(acc_query.getColumn(1).getInt());
			string type = acc_query.getColumn(2).getText();
			double balance = acc_query.getColumn(3).getDouble();

			Customer *c = get_customer(cust_id);
			if (c)
				c->add_account(Account(acc_id, type, balance));
		}

	} catch (std::exception &e) {
		std::cerr << e.what() << '\n';
	}
}

Customer *Bank::get_customer(int ID) {
	for (auto &c : customers)
		if (c.get_id() == ID)
			return &c;

	return nullptr;
}

vector<Customer> Bank::get_customers() const { return customers; }

#pragma mark - Operations
std::expected<void, string> Bank::deposit //
    (Customer &customer, Account &account, double amount) {

	if (amount < 0.0)
		return std::unexpected("error negative amount");

	account.add_to_balance(amount);

	auto result = update_account(customer, account);
	if (!result)
		return std::unexpected(result.error());

	return {};
}

std::expected<void, string> Bank::withdraw //
    (Customer &customer, Account &account, double amount) {

	if (amount < 0.0)
		return std::unexpected("error negative amount");

	if (account.get_balance() <= amount)
		return std::unexpected("balance too low for operation");

	account.take_from_balance(amount);

	auto result = update_account(customer, account);
	if (!result)
		return std::unexpected(result.error());

	return {};
}

std::expected<void, string> Bank::transfer //
    (Customer &from_customer, Account &from_acc, Customer &to_customer,
     Account &to_acc, double amount) {

	if (from_customer.get_id() == to_customer.get_id())
		return std::unexpected("Error cannot transfer money to self");

	if (amount < 0.0)
		return std::unexpected("Error negative amount");

	if (from_acc.get_balance() < amount)
		return std::unexpected("Balance too low");

	try {

		db.exec("BEGIN TRANSACTION;");

		from_acc.take_from_balance(amount);
		to_acc.add_to_balance(amount);

		// Update account A
		auto update_A = update_account(from_customer, from_acc);
		if (!update_A)
			return std::unexpected(update_A.error());

		// Update account B
		auto update_B = update_account(to_customer, to_acc);
		if (!update_B)
			return std::unexpected(update_B.error());

		db.exec("COMMIT;");

	} catch (const std::exception &e) {
		db.exec("ROLLBACK;");
		return std::unexpected(std::string("Transfer failed: ") + e.what());
	}

	return {};
}

#pragma mark - Updates
std::expected<void, string> Bank::update_account //
    (Customer &customer, Account &account) {
	try {

		SQLite::Statement query(db, "UPDATE accounts SET balance = ? WHERE id "
		                            "= ? AND customer_id = ?;");

		query.bind(1, account.get_balance());
		query.bind(2, account.get_id());
		query.bind(3, customer.get_id());
		query.exec();

	} catch (std::exception &e) {
		return std::unexpected //
		    (std::string("Failed to update account in DB: ") + e.what());
	}

	return {};
}
