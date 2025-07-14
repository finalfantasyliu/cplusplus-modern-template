cmake_minimum_required(VERSION 3.31)

add_library(test_static STATIC
        test_static.cpp
)
# Tell the compiler we are *building* the DLL, not using it
target_compile_definitions(test_static PRIVATE MYLIB_BUILD)

target_include_directories(test_static PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
