//
//  main.cpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#include "bank.hpp"
#include "output.hpp"
#include <iostream>
#include <limits>
#include <sstream>

void add_customer(Bank &bank);
void create_account_for(Bank &bank);
void deposit(Bank &bank);
void history(Bank &bank);
void list_customers(const Bank &bank);
void transfer(Bank &bank);
void withdraw(Bank &bank);

void pause();
void clear();

int main(int argc, char *argv[]) { //
	std::filesystem::path exec = std::filesystem::canonical(argv[0]);
	std::filesystem::path exe_dir = exec.parent_path() / "data";

	// Initialize data directory
	if (!std::filesystem::exists(exe_dir))
		std::filesystem::create_directory(exe_dir);

	// Initialize database
	Bank bank(exe_dir / "bank.db");
	if (!bank.init())
		throw std::runtime_error("error initializing database");

	bank.load_customers();
	bank.load_history();

	// Menu loop
	bool runs = true;

	while (runs) {
		out::blue << "=== Banking Simulation ===" << '\n' //
		          << "What do you want to do :" << '\n';

		std::cout << "1) Add customer" << '\n'        //
		          << "2) List customers" << '\n'      //
		          << "3) Create account" << '\n'      //
		          << "4) Deposit" << '\n'             //
		          << "5) Withdraw" << '\n'            //
		          << "6) Transfer" << '\n'            //
		          << "7) Transaction history" << '\n' //
		          << "0) Exit" << '\n';

		out::blue << "\n-> ";

		std::string line;
		getline(std::cin, line);

		int choice;
		try {
			choice = stoi(line);
		} catch (...) {
			out::red << "Invalid input\n";
			pause();
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
			withdraw(bank);
			break;

		case 6:
			transfer(bank);
			break;

		case 7:
			history(bank);
			break;

		case 0:
			runs = false;
			break;

		default:
			break;
		}

		std::cout << '\n';
	}

	out::blue << "Goodbye! \n";
	return EXIT_SUCCESS;
}

void add_customer(Bank &bank) {
	int cust_id;
	std::string cust_name;

	out::blue << "=== Banking Simulation ===" << '\n';

	out::blue << "Customer ID -> ";

	std::string line;
	getline(std::cin, line);

	try {
		cust_id = stoi(line);
		if (cust_id < 0) {
			out::red << "Invalid ID\n";
			pause();
			return;
		}

	} catch (...) {
		out::red << "Invalid ID\n";
		pause();
		return;
	}

	out::blue << "Customer name -> ";
	getline(std::cin, cust_name);

	Customer cust(cust_id, cust_name);
	bank.add_customer(cust);

	out::blue << "\ncustomer added\n";
	pause();
}

void list_customers(const Bank &bank) {
	out::blue << "=== Banking Simulation ===" << '\n';

	for (const auto &cust : bank.get_customers()) {
		std::stringstream cust_str;
		cust_str << cust.get_id() << " : " << cust.get_name();

		std::cout << std::setw(20) << std::left << cust_str.str();

		if (!cust.get_accounts().empty())
			std::cout << "[ ";

		int idx = 0;
		for (const auto &acc : cust.get_accounts()) {
			std::cout << acc.get_id() << " - " << acc.get_type() //
			          << " : " << acc.get_balance() << "€";

			if (idx++ < cust.get_accounts().size() - 1)
				std::cout << "  |  ";
		}

		if (!cust.get_accounts().empty())
			std::cout << " ]";

		std::cout << '\n';
	}

	std::cout << '\n';

	pause();
}

void create_account_for(Bank &bank) {
	out::blue << "=== Banking Simulation ===" << '\n';

	int customer_id;
	out::blue << "Customer ID -> ";

	std::string cust_id_str;
	getline(std::cin, cust_id_str);

	try {
		customer_id = stoi(cust_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Customer *customer = bank.get_customer(customer_id);

	if (!customer) {
		out::red << "customer not found with ID " << customer_id;
		return;
	}

	std::cout << customer->get_name() << "\n\n";

	// Get ID
	int acc_id;
	out::blue << "Accound ID -> ";

	std::string str_id;
	getline(std::cin, str_id);

	try {
		acc_id = stoi(str_id);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	// Get Type
	out::blue << "Account type -> ";
	std::string acc_type;
	getline(std::cin, acc_type);

	Account acc(acc_id, acc_type, 0.0);

	bank.add_account_for_customer(*customer, acc);
}

void deposit(Bank &bank) {
	out::blue << "=== Banking Simulation ===" << '\n';

	int customer_id;
	out::blue << "Customer ID -> ";

	std::string cust_id_str;
	getline(std::cin, cust_id_str);

	try {
		customer_id = stoi(cust_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Customer *customer = bank.get_customer(customer_id);

	if (!customer) {
		out::red << "customer not found with ID " << customer_id << '\n';

		pause();

		return;
	}
	std::cout << customer->get_name() << "\n\n";

	// Get account ID
	int account_id;
	std::cout << "Account ID -> ";

	std::string acc_id_str;
	getline(std::cin, acc_id_str);

	try {
		account_id = stoi(acc_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Account *account = customer->get_account(account_id);

	if (!account) {
		out::red << "account not found with ID " << account_id << '\n';

		pause();

		return;
	}
	std::cout << account->get_type() << "\n\n";

	// Get amount
	double amount;
	std::cout << "Amount to deposit -> ";

	std::string amount_str;
	getline(std::cin, amount_str);

	try {
		amount = stod(amount_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	auto result = bank.deposit(*customer, *account, amount);

	if (result) {
		out::green << "Balance = " << account->get_balance() << '\n';
	} else {
		out::red << result.error() << '\n';
		std::cout << "Balance = " << account->get_balance() << '\n';
	}

	pause();
}

void withdraw(Bank &bank) {
	out::blue << "=== Banking Simulation ===" << '\n';

	int customer_id;
	std::cout << "Customer ID -> ";

	std::string cust_id_str;
	getline(std::cin, cust_id_str);

	try {
		customer_id = stoi(cust_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Customer *customer = bank.get_customer(customer_id);

	if (!customer) {
		out::red << "customer not found with ID " << customer_id << '\n';

		pause();

		return;
	}
	std::cout << customer->get_name() << "\n\n";

	// Get account ID
	int account_id;
	out::blue << "Account ID -> ";

	std::string acc_id_str;
	getline(std::cin, acc_id_str);

	try {
		account_id = stoi(acc_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Account *account = customer->get_account(account_id);

	if (!account) {
		out::red << "account not found with ID " << account_id << '\n';

		pause();

		return;
	}
	std::cout << account->get_type() << "\n\n";

	// Get amount
	double amount;
	out::blue << "Amount to withdraw -> ";

	std::string amount_str;
	getline(std::cin, amount_str);

	try {
		amount = stod(amount_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	//

	auto result = bank.withdraw(*customer, *account, amount);

	if (result) {
		out::green << "Balance = " << account->get_balance() << '\n';
	} else {
		out::red << result.error() << '\n';
		std::cout << "Balance = " << account->get_balance() << '\n';
	}

	//

	pause();
}

void transfer(Bank &bank) {
	out::blue << "=== Banking Simulation ===" << '\n';

	// Get customer_A
	int customer_A_id;
	out::blue << "Customer_A ID -> ";

	std::string cust_A_id_str;
	getline(std::cin, cust_A_id_str);

	try {
		customer_A_id = stoi(cust_A_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Customer *customer_A = bank.get_customer(customer_A_id);

	if (!customer_A) {
		out::red << "customer not found with ID " << customer_A_id << '\n';

		pause();

		return;
	}
	std::cout << customer_A->get_name() << "\n\n";

	// Get account_A ID
	int account_A_id;
	out::blue << "Account_A ID -> ";

	std::string acc_A_id_str;
	getline(std::cin, acc_A_id_str);

	try {
		account_A_id = stoi(acc_A_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Account *account_A = customer_A->get_account(account_A_id);

	if (!account_A) {
		out::red << "account not found with ID " << account_A_id << '\n';

		pause();

		return;
	}
	std::cout << account_A->get_type() << "\n\n";

	//--------------------------------------------

	// Get customer_B
	int customer_B_id;
	out::blue << "Customer_B ID -> ";

	std::string cust_B_id_str;
	getline(std::cin, cust_B_id_str);

	try {
		customer_B_id = stoi(cust_B_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Customer *customer_B = bank.get_customer(customer_B_id);

	if (!customer_B) {
		out::red << "customer not found with ID " << customer_B_id << '\n';

		pause();

		return;
	}
	std::cout << customer_B->get_name() << "\n\n";

	// Get account_B ID
	int account_B_id;
	out::blue << "Account_B ID -> ";

	std::string acc_B_id_str;
	getline(std::cin, acc_B_id_str);

	try {
		account_B_id = stoi(acc_B_id_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	Account *account_B = customer_B->get_account(account_B_id);

	if (!account_B) {
		out::red << "account not found with ID " << account_B_id << '\n';

		pause();

		return;
	}
	std::cout << account_B->get_type() << "\n\n";

	//--------------------------------------------

	// Get amount
	double amount;
	out::blue << "Amount to transfer -> ";

	std::string amount_str;
	getline(std::cin, amount_str);

	try {
		amount = stod(amount_str);
	} catch (...) {
		out::red << "Invalid input\n";
		pause();
		return;
	}

	//

	auto result = bank.transfer //
	              (*customer_A, *account_A, *customer_B, *account_B, amount);

	if (!result) {
		out::red << result.error() << '\n';

		pause();

		return;
	}

	std::cout << "New balances\n";

	out::green << '\t' << customer_A->get_name() << " : "
	           << account_A->get_balance() << '\n'

	           << '\t' << customer_B->get_name() << " : "
	           << account_B->get_balance() << '\n';

	//

	pause();
}

void history(Bank &bank) {
	out::blue << "=== Banking Simulation ===" << '\n';

	for (const auto &trans : bank.get_history()) {

		std::cout << trans.id << " : "

		          << "from " << (trans.from ? trans.from->get_name() : "_")

		          << " to " << (trans.to ? trans.to->get_name() : "_")

		          << " -> " << trans.amount << "€" << '\n';
	}

	pause();
}

void pause() {
	out::yellow << "\nPress ENTER to continue...";
	std::string _;
	getline(std::cin, _);

	clear();
	return;
}

void clear() { //
	std::cout << "\033[2J\033[H" << std::flush;
}
