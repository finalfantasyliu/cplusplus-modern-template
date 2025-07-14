// test_class_template.cpp
#include "test_class_template.h"
#include <iostream>

template<typename T>
void X2<T>::f() {
    std::cout << "X2<T>::f\n";
}
template<typename T>
void X2<T>::f2() {
    std::cout << "X2<T>::f2\n";
}

// **After** the body is visible, generate the object code once
//這個只有個別instantiate member function
//template void X2<int>::f();
//template void X2<int>::f2();


//這個是instantiate 所有member function
template struct X2<int>;