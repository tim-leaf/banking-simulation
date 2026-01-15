//
//  transaction.cpp
//  SQL Banking Simulation
//
//  Created by Tim Le Flem on 15/01/2026.
//

#include "transaction.hpp"

Transaction::Transaction //
    (Customer *from, Customer *to, double amount, const std::string &type,
     int id)
    : from(from), to(to), id(id), amount(amount), type(type) {}
