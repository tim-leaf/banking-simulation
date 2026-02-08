cmake_minimum_required(VERSION 3.16)

project(BankingSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(BankingSimulation
    src/main.cpp
    src/account.cpp
    src/customer.cpp
    src/bank.cpp
    src/transaction.cpp
)

target_include_directories(BankingSimulation PRIVATE include)

# ---- SQLiteCpp ----
find_package(SQLiteCpp REQUIRED)

target_link_libraries(BankingSimulation PRIVATE SQLiteCpp)
