cmake_minimum_required(VERSION 3.31)
project(test_enum_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_enum_2 main.cpp
        enum_operation.hpp
        license_status.hpp)
