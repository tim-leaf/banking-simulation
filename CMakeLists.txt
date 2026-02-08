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
include(FetchContent)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG master
)

FetchContent_MakeAvailable(SQLiteCpp)

target_link_libraries(BankingSimulation PRIVATE SQLiteCpp sqlite3)