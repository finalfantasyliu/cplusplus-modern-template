#include <iostream>
//模版模版形參的語法如下
template<template<typename T> class T>
struct X {
    T<int>t;
};

//gcc可過但clang不行，模版模版形參是c++11引入，但若要聲明typename需要c++17，c++17以前必須使用class取代typename
template<template<typename T> typename T>
struct Z {

};

template<typename T>
struct Y {
    void f()const {std::puts("y");}
};

template<typename T>
struct Y2 {

};
//模版模版形參可以有預設值，跟一般的function template一致，也可以把佔位符class T的T省略，如果你不用他的話
template<template<typename T> class =Y2, typename =int,std::size_t=10>
struct Z1 {

};
//class template 也可以用variadic template，
template <typename ... Args>
struct Z2 {

};

//大陸稱模版模版形參包，記得是要在class後面加dot
template<template<typename T> class ... T>
struct Z3 {

};
//若要使用non-type template的模版模版class，需使用這樣的方式
template<size_t>
struct Y3 {

};
template<template<size_t>class T>
struct Z4 {

};
//若要使用接受類模版模版形參包的類模版如下所示
template<typename ... Args>
struct X4 {

};
template<template<typename ... Args>class T>
struct Z5 {

};
//其實掌握一個通則，若要撰寫特殊的類模版，只需複製基礎模版template至你需要的類模版template中，再加上class即可，如上所示
int main() {
    X<Y>x ;
    x.t.f();
    Z1();
    Z2<int,std::string,double>();
    Z3<Y2,Y>();
    Z4<Y3>();
    return 0;
}