cmake_minimum_required(VERSION 3.31)
project(15_class_template_document)

set(CMAKE_CXX_STANDARD 20)

add_executable(15_class_template_document main.cpp
        test_class.cpp
        test_class.hpp
        test_class_template.cpp
        test_class_template.hpp)
