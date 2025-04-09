
cmake_minimum_required(VERSION 3.30)
project(domain_design_and_implementation)

set(CMAKE_CXX_STANDARD 23)

include_directories(test/include
        src/include)

add_executable(test_domain_design_and_implementation
        test/include/catch.hpp
        test/test.cpp
        test/testWarehouse.cpp
        src/employee.cpp
        src/pallet.cpp
        src/shelf.cpp
        src/warehouse.cpp
        src/include/IContainer.hpp)

add_executable(domain_design_and_implementation
        main.cpp
        src/employee.cpp
        src/pallet.cpp
        src/shelf.cpp
        src/warehouse.cpp
        src/include/IContainer.hpp)
