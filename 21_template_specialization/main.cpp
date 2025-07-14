#include <iostream>
#include <type_traits>

template<typename T, typename T2>
auto f(const T& a, const T2 &b) {
    return a+b; //主函式模版
}

//如果你傳一個double與int類型，並且想要他相減，就可以使用全特化
template<>
    auto  f<double, int>(const double & a, const int &b) { //全特化
    return a-b;
}

struct X {
    void f()const{}
};

struct X2 {
    void f2()const{}
};
template<typename T>
void test(const T& t) {
    t.f();
}

int main() {
    std::cout<<f(2,2)<<std::endl;
    //std::cout<<f(2.5,1)<<std::endl;

    //std::cout<<f<double,int>(1,0)<<std::endl;
X x;
    X2 x2;
    test(x);
    test(x2);
    return 0;
}