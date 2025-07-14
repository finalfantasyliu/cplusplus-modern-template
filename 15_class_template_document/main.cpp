#include <iostream>
#include "test_class.hpp"
#include "test_class_template.hpp"
int main() {
    X2<int> x2; //這個可以過乃你有實際的class template definition
    //但這個沒有，因為他找不到實際的definition，無法實體化，
    //因為其沒有跟class template一起實體化，test_class_template.o X2<T>::f還是維持非實體化的狀態
    //所以當main.cpp當要link時就找不到symbol
    x2.f();
    return 0;
}