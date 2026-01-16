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
inline ColorStream magenta("\033[35m");
inline ColorStream cyan("\033[36m");

} // namespace out
