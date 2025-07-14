#include <iostream>

template <typename T, typename T2>
struct X {
    void f() const;
};

template <typename T>
struct X<void,T> {

    void f2() const ;
    //void f2(){};
    int a{};
};
//類外定義的寫法，但通常不建議類外定義
template <typename T>
void X<void,T>::f2() const{
}

template<typename T,std::size_t N>
struct X2 {
    template<typename T_, typename T2>
    struct Y{};
};
//這是X2為explicit specialization，Y才是partial specialization
template<>
template<typename T2>
struct X2<int,1>::Y<int,T2> {
    void f() const{};
};


int main() {
    X<void,int>x;
    x.f2();
    X <int,int> x2;
    x2.f();

    X2<int,1>::Y<int, void> y2;
    y2.f();
    X2<int,1>::Y<void, void> y3;
    //這邊會match到primary template，所以不會有f這個function
    //y3.f()
    return 0;
}