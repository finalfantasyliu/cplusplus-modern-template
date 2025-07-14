//
// Created by finalfantasyliu on 2025/7/7.
//

#include "test_dylib.h"


template<typename T>
void f(T) {
    std::cout<<typeid(T).name()<<std::endl;
}
//基本上macos與linux的attribute如果不特別寫都是visible，但這邊示範所以寫一下
#define API __attribute__((visibility("default")))

template API void f<int>(int);
template API void f<std::string>(std::string);


template<typename T>
void X<T>::f() {
    std::cout<<"X<T>::f()"<<std::endl;
}

template struct API X<int>;
template struct API X<std::string>;
