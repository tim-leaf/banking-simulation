//
//  output.hpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 15/01/2026.
//

#pragma once
#include <iostream>

namespace out {

class ColorStream {
	const char *code; // ANSI color code
 public:
	ColorStream(const char *c) : code(c) {}

	template <typename T> //
	ColorStream &operator<<(const T &value) {
		std::cout << code << value << "\033[0m";
		return *this;
	}
};

// Predefined colors
inline ColorStream green("\033[32m");
inline ColorStream red("\033[31m");
inline ColorStream yellow("\033[33m");
inline ColorStream blue("\033[34m");

} // namespace out
