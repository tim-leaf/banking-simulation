//
//  main.cpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 14/01/2026.
//

#include <iostream>

int main() {
	bool runs = true;

	while (runs) {
		std::cout << "=== Banking Simulation ===" << '\n' //
		          << "What do you want to do :" << '\n'   //
		          << "1) Add customer" << '\n'            //
		          << "2) List customers" << '\n'          //
		          << "3) Create account" << '\n'          //
		          << "4) Deposit" << '\n'                 //
		          << "5) Transfer" << '\n'                //
		          << "0) Exit" << '\n';

		int choice;
		std::cout << "\n-> ";
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear(); // clear error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max());
			std::cout << "Invalid input! Please enter a number.\n\n";
			continue;
		}

		switch (choice) {
		case 1:
			//
			break;

		case 2:
			//
			break;

		case 3:
			//
			break;

		case 4:
			//
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

		std::cout << '\n';
	}

	std::cout << "Goodbye!\n";
	return EXIT_SUCCESS;
}
