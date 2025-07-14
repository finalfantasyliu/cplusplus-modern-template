#include <iostream>
#include "test/test_static.h"
int main() {
    f<int>(1);
    f<std::string>("1");
    return 0;
}