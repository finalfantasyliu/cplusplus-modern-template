cmake_minimum_required(VERSION 3.31)

add_library(test_dylib SHARED
        test_dylib.cpp
)
# Tell the compiler we are *building* the DLL, not using it
target_compile_definitions(test_dylib PRIVATE MYLIB_BUILD)

target_include_directories(test_dylib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
