#include <iostream>
#include "test/test_dylib.h"
using namespace std::literals;
int main() {
    f<int>(1);
    f<std::string>("1"s);
    return 0;
}