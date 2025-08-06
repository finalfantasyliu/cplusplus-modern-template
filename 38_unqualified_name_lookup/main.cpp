#include <iostream>
void f() {
    std::cout<<"全局\n";
}

template<class T>
struct X {
    void f()const {std::cout<<"X\n";}
};
template<class T>
struct Y:X<T> {
    void f() const  {
        std::cout<<"Y\n";
    };
    using X<T>::f;
    void t1() const {
        this->f(); //這邊是unqualified name，但他指定的基底類別(除非你的子類有同名的function)，基底類別又依賴T，所以是dependent name，所以會推遲到第二階段查找，
    }
    void t2()const {
        f(); //這個也是unqualified name，但沒有相依，
    }
};
struct X1 {
    void f()const{std::cout<<"X1\n";}
};

struct Y1:X1 {
void f() const  {
    std::cout<<"Y1\n";
};
    void t1()const {
        this->f();
    }
    void t2() {
        f();
    }
};
struct Z {
    void f() {
        std::cout<<"Z\n";
    }
};
struct Z1:Z {
    void f() {
        std::cout<<"Z1\n";
    }
};

int main() {

    Y<void> y;
    y.t1();
    y.t2();


    Y1 y1;
    y1.t1();
    y1.t2();
    Z1 z1;
    z1.f();
    return 0 ;
}