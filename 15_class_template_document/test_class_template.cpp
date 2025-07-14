//
// Created by finalfantasyliu on 2025/6/23.
//

#include "test_class_template.hpp"

#include <iostream>
#include <__ostream/basic_ostream.h>

//切記不管是class template或function template放在cpp的file中，
//什麼東西都不會產生，因為沒有實體化的程式，所以不會替代任何function
template<typename T>
void X2<T>::f() {
    std::cout << "X2 function called" << std::endl;
}
//記得不能用這個，因為其實test_class_template的class已經有definition，
//所以會有duplicate symbol，但如果你還是想聲明，可以使用extern template X2<T>()
//extern template X2<T>()
template void X2<int>::f();