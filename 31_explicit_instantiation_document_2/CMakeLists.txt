cmake_minimum_required(VERSION 3.31)
project(31_explicit_instantiation_document_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(31_explicit_instantiation_document_2 main.cpp
        test_class_template.cpp)
