cmake_minimum_required(VERSION 3.31)
project(32_explicit_instantiate_dylib)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(test)

add_executable(32_explicit_instantiate_dylib main.cpp
)
target_link_libraries(32_explicit_instantiate_dylib PRIVATE test_dylib)