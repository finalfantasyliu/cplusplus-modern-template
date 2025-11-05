#include <iostream>
#include <ostream>
#include "test.h"
//
// Created by finalfantasyliu on 2025/11/4.
//
template<typename T>
void f(const T& t) {
    std::cout<<t<<std::endl;
}
//這是顯示實例化
//template void f<int>(const int& t);
//全特化
template <>
void f(const int& t) {
    std::cout<<"f<int>"<<std::endl;
}

template<typename T>
void X<T>::f() {
    std::cout << "f: " << typeid(T).name() << "a: " << this->a << std::endl;
}

//template struct X<int>;

template<>
void X<int>::f() {
    std::cout<<"X<int>::f() full specialization"<<std::endl;
}
