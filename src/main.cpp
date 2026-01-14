//
//  main.cpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#include "bank.hpp"
#include <iostream>
#include <limits>

using std::cerr, std::cin, std::cout, std::getline, std::stod, std::stoi;

void add_customer(Bank &bank);
void create_account_for(Bank &bank);
void deposit(Bank &bank);
void list_customers(const Bank &bank);

int main() {
	Bank bank("data/bank.db");
	if (!bank.init())
		throw std::runtime_error("error initializing database");

	bank.load_customers();

	bool runs = true;

	while (runs) {
		cout << "=== Banking Simulation ===" << '\n' //
		     << "What do you want to do :" << '\n'   //
		     << "1) Add customer" << '\n'            //
		     << "2) List customers" << '\n'          //
		     << "3) Create account" << '\n'          //
		     << "4) Deposit" << '\n'                 //
		     << "5) Transfer" << '\n'                //
		     << "0) Exit" << '\n';

		cout << "\n-> ";

		string line;
		getline(cin, line);

		int choice;
		try {
			choice = stoi(line);
		} catch (...) {
			cerr << "Invalid input\n";
			continue;
		}

		switch (choice) {
		case 1:
			add_customer(bank);
			break;

		case 2:
			list_customers(bank);
			break;

		case 3:
			create_account_for(bank);
			break;

		case 4:
			deposit(bank);
			break;

		case 5:
			//
			break;

		case 6:
			//
			break;

		case 0:
			runs = false;
			break;

		default:
			break;
		}

		cout << '\n';
	}

	cout << "Goodbye!\n";
	return EXIT_SUCCESS;
}

void add_customer(Bank &bank) {
	int cust_id;
	string cust_name;

	cout << "=== Banking Simulation ===" << '\n';

	cout << "Customer ID -> ";

	string line;
	getline(cin, line);

	try {
		cust_id = stoi(line);
		if (cust_id < 0) {
			cout << "Invalid ID\n";
			return;
		}

	} catch (...) {
		cout << "Invalid ID\n";
		return;
	}

	cout << "Customer name -> ";
	getline(cin, cust_name);

	Customer cust(cust_id, cust_name);
	bank.add_customer(cust);

	cout << "\ncustomer added\n";
}

void list_customers(const Bank &bank) {
	cout << "=== Banking Simulation ===" << '\n';

	for (const auto &cust : bank.get_customers()) {
		cout << cust.get_id() << " : " << cust.get_name() << '\t';

		if (!cust.get_accounts().empty())
			std::cout << "[ ";

		int idx = 0;
		for (const auto &acc : cust.get_accounts()) {
			cout << acc.get_id() << " - " << acc.get_type() //
			     << " : " << acc.get_balance() << "€";

			if (idx++ >= cust.get_accounts().size())
				std::cout << '\t';
		}

		if (!cust.get_accounts().empty())
			std::cout << " ]";
	}

	std::cout << '\n';

	cout << "\nPress ENTER to continue...";
	string _;
	getline(cin, _);
}

void create_account_for(Bank &bank) {
	cout << "=== Banking Simulation ===" << '\n';

	int customer_id;
	cout << "Customer ID -> ";

	string cust_id_str;
	getline(cin, cust_id_str);

	try {
		customer_id = stoi(cust_id_str);
	} catch (...) {
		cerr << "Invalid input\n";
		return;
	}

	Customer *customer = bank.get_customer(customer_id);

	if (!customer) {
		cerr << "customer not found with ID " << customer_id;
		return;
	}

	std::cout << customer->get_name() << "\n\n";

	// Get ID
	int acc_id;
	std::cout << "Accound ID -> ";

	string str_id;
	getline(cin, str_id);

	try {
		acc_id = stoi(str_id);
	} catch (...) {
		std::cout << "Invalid input\n";
		return;
	}

	// Get Type
	std::cout << "Account type -> ";
	string acc_type;
	getline(cin, acc_type);

	Account acc(acc_id, acc_type, 0.0);

	bank.add_account_for_customer(*customer, acc);
}

void deposit(Bank &bank) {
	cout << "=== Banking Simulation ===" << '\n';

	int customer_id;
	cout << "Customer ID -> ";

	string cust_id_str;
	getline(cin, cust_id_str);

	try {
		customer_id = stoi(cust_id_str);
	} catch (...) {
		cerr << "Invalid input\n";
		return;
	}

	Customer *customer = bank.get_customer(customer_id);

	if (!customer) {
		cerr << "customer not found with ID " << customer_id;
		return;
	}
	std::cout << customer->get_name() << "\n\n";

	// Get account ID
	int account_id;
	cout << "Account ID -> ";

	string acc_id_str;
	getline(cin, acc_id_str);

	try {
		account_id = stoi(acc_id_str);
	} catch (...) {
		cerr << "Invalid input\n";
		return;
	}

	Account *account = customer->get_account(account_id);

	if (!account) {
		cerr << "customer not found with ID " << customer_id;
		return;
	}
	std::cout << account->get_type() << "\n\n";

	// Get amount
	double amount;
	cout << "Amount to deposit -> ";

	string amount_str;
	getline(cin, amount_str);

	try {
		amount = stod(amount_str);
	} catch (...) {
		cerr << "Invalid input\n";
		return;
	}

	bank.deposit(*customer, *account, amount);
}
