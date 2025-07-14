#include <iostream>
#include <type_traits>

 template<typename T> //主模版
struct is_void {
     static constexpr bool value=false;
 };
//這兩個實體化之後，並沒有相關性，而其內部的static variable是屬於class，而不屬於class template
template<>
struct is_void<void> {
    static constexpr bool value=true;
};

template<typename T>
constexpr bool is_void_v=is_void<T>::value;

template<typename T>
struct X {
    void f()const {
        std::puts("f");
    }
};
template<>
struct X<int> {
    void f() const {
        std:puts("f<int>");
    }
    void f2()const{};
    int n;
};
int main() {
    std::cout<<std::boolalpha<< is_void<void>::value<<std::endl;
    std::cout<<std::boolalpha<<is_void_v<void><<std::endl;
    std::cout<<std::boolalpha<<is_void<int>::value<<std::endl;
    X<void> x;
    return 0;
}